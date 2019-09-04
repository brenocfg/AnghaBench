#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pkcs7_signed_info {size_t msgdigest_len; int /*<<< orphan*/  aa_set; void const* msgdigest; int /*<<< orphan*/  signing_time; int /*<<< orphan*/  index; } ;
struct pkcs7_parse_context {int last_oid; TYPE_1__* msg; struct pkcs7_signed_info* sinfo; } ;
typedef  enum OID { ____Placeholder_OID } OID ;
struct TYPE_2__ {int data_type; } ;

/* Variables and functions */
 unsigned char ASN1_OTS ; 
 int EBADMSG ; 
 int EKEYREJECTED ; 
#define  OID_contentType 133 
#define  OID_messageDigest 132 
 int OID_msIndirectData ; 
#define  OID_msSpOpusInfo 131 
#define  OID_msStatementType 130 
#define  OID_signingTime 129 
#define  OID_smimeCapabilites 128 
 int /*<<< orphan*/  __test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int look_up_OID (void const*,size_t) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned char,size_t,unsigned int,void const*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  sinfo_has_content_type ; 
 int /*<<< orphan*/  sinfo_has_message_digest ; 
 int /*<<< orphan*/  sinfo_has_ms_opus_info ; 
 int /*<<< orphan*/  sinfo_has_ms_statement_type ; 
 int /*<<< orphan*/  sinfo_has_signing_time ; 
 int /*<<< orphan*/  sinfo_has_smime_caps ; 
 int x509_decode_time (int /*<<< orphan*/ *,size_t,unsigned char,void const*,size_t) ; 

int pkcs7_sig_note_authenticated_attr(void *context, size_t hdrlen,
				      unsigned char tag,
				      const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;
	struct pkcs7_signed_info *sinfo = ctx->sinfo;
	enum OID content_type;

	pr_devel("AuthAttr: %02x %zu [%*ph]\n", tag, vlen, (unsigned)vlen, value);

	switch (ctx->last_oid) {
	case OID_contentType:
		if (__test_and_set_bit(sinfo_has_content_type, &sinfo->aa_set))
			goto repeated;
		content_type = look_up_OID(value, vlen);
		if (content_type != ctx->msg->data_type) {
			pr_warn("Mismatch between global data type (%d) and sinfo %u (%d)\n",
				ctx->msg->data_type, sinfo->index,
				content_type);
			return -EBADMSG;
		}
		return 0;

	case OID_signingTime:
		if (__test_and_set_bit(sinfo_has_signing_time, &sinfo->aa_set))
			goto repeated;
		/* Should we check that the signing time is consistent
		 * with the signer's X.509 cert?
		 */
		return x509_decode_time(&sinfo->signing_time,
					hdrlen, tag, value, vlen);

	case OID_messageDigest:
		if (__test_and_set_bit(sinfo_has_message_digest, &sinfo->aa_set))
			goto repeated;
		if (tag != ASN1_OTS)
			return -EBADMSG;
		sinfo->msgdigest = value;
		sinfo->msgdigest_len = vlen;
		return 0;

	case OID_smimeCapabilites:
		if (__test_and_set_bit(sinfo_has_smime_caps, &sinfo->aa_set))
			goto repeated;
		if (ctx->msg->data_type != OID_msIndirectData) {
			pr_warn("S/MIME Caps only allowed with Authenticode\n");
			return -EKEYREJECTED;
		}
		return 0;

		/* Microsoft SpOpusInfo seems to be contain cont[0] 16-bit BE
		 * char URLs and cont[1] 8-bit char URLs.
		 *
		 * Microsoft StatementType seems to contain a list of OIDs that
		 * are also used as extendedKeyUsage types in X.509 certs.
		 */
	case OID_msSpOpusInfo:
		if (__test_and_set_bit(sinfo_has_ms_opus_info, &sinfo->aa_set))
			goto repeated;
		goto authenticode_check;
	case OID_msStatementType:
		if (__test_and_set_bit(sinfo_has_ms_statement_type, &sinfo->aa_set))
			goto repeated;
	authenticode_check:
		if (ctx->msg->data_type != OID_msIndirectData) {
			pr_warn("Authenticode AuthAttrs only allowed with Authenticode\n");
			return -EKEYREJECTED;
		}
		/* I'm not sure how to validate these */
		return 0;
	default:
		return 0;
	}

repeated:
	/* We permit max one item per AuthenticatedAttribute and no repeats */
	pr_warn("Repeated/multivalue AuthAttrs not permitted\n");
	return -EKEYREJECTED;
}
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
struct pkcs7_signed_info {scalar_t__ signing_time; int /*<<< orphan*/  index; int /*<<< orphan*/  sig; TYPE_1__* signer; int /*<<< orphan*/  aa_set; } ;
struct pkcs7_message {int dummy; } ;
struct TYPE_2__ {scalar_t__ valid_from; scalar_t__ valid_to; int /*<<< orphan*/  pub; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EKEYREJECTED ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 int pkcs7_digest (struct pkcs7_message*,struct pkcs7_signed_info*) ; 
 int pkcs7_find_key (struct pkcs7_message*,struct pkcs7_signed_info*) ; 
 int pkcs7_verify_sig_chain (struct pkcs7_message*,struct pkcs7_signed_info*) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int public_key_verify_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sinfo_has_signing_time ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkcs7_verify_one(struct pkcs7_message *pkcs7,
			    struct pkcs7_signed_info *sinfo)
{
	int ret;

	kenter(",%u", sinfo->index);

	/* First of all, digest the data in the PKCS#7 message and the
	 * signed information block
	 */
	ret = pkcs7_digest(pkcs7, sinfo);
	if (ret < 0)
		return ret;

	/* Find the key for the signature if there is one */
	ret = pkcs7_find_key(pkcs7, sinfo);
	if (ret < 0)
		return ret;

	if (!sinfo->signer)
		return 0;

	pr_devel("Using X.509[%u] for sig %u\n",
		 sinfo->signer->index, sinfo->index);

	/* Check that the PKCS#7 signing time is valid according to the X.509
	 * certificate.  We can't, however, check against the system clock
	 * since that may not have been set yet and may be wrong.
	 */
	if (test_bit(sinfo_has_signing_time, &sinfo->aa_set)) {
		if (sinfo->signing_time < sinfo->signer->valid_from ||
		    sinfo->signing_time > sinfo->signer->valid_to) {
			pr_warn("Message signed outside of X.509 validity window\n");
			return -EKEYREJECTED;
		}
	}

	/* Verify the PKCS#7 binary against the key */
	ret = public_key_verify_signature(sinfo->signer->pub, sinfo->sig);
	if (ret < 0)
		return ret;

	pr_devel("Verified signature %u\n", sinfo->index);

	/* Verify the internal certificate chain */
	return pkcs7_verify_sig_chain(pkcs7, sinfo);
}
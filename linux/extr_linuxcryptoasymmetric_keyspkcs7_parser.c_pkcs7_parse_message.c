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
struct x509_certificate {struct x509_certificate* next; } ;
struct public_key_signature {int dummy; } ;
struct pkcs7_signed_info {int dummy; } ;
struct pkcs7_parse_context {unsigned long data; struct pkcs7_message* msg; TYPE_1__* sinfo; struct x509_certificate* certs; int /*<<< orphan*/ * ppsinfo; struct x509_certificate** ppcerts; } ;
struct pkcs7_message {int /*<<< orphan*/  signed_infos; } ;
struct TYPE_2__ {void* sig; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct pkcs7_message* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int asn1_ber_decoder (int /*<<< orphan*/ *,struct pkcs7_parse_context*,void const*,size_t) ; 
 int /*<<< orphan*/  kfree (struct pkcs7_parse_context*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pkcs7_check_authattrs (struct pkcs7_message*) ; 
 int /*<<< orphan*/  pkcs7_decoder ; 
 int /*<<< orphan*/  pkcs7_free_message (struct pkcs7_message*) ; 
 int /*<<< orphan*/  pkcs7_free_signed_info (TYPE_1__*) ; 
 int /*<<< orphan*/  x509_free_certificate (struct x509_certificate*) ; 

struct pkcs7_message *pkcs7_parse_message(const void *data, size_t datalen)
{
	struct pkcs7_parse_context *ctx;
	struct pkcs7_message *msg = ERR_PTR(-ENOMEM);
	int ret;

	ctx = kzalloc(sizeof(struct pkcs7_parse_context), GFP_KERNEL);
	if (!ctx)
		goto out_no_ctx;
	ctx->msg = kzalloc(sizeof(struct pkcs7_message), GFP_KERNEL);
	if (!ctx->msg)
		goto out_no_msg;
	ctx->sinfo = kzalloc(sizeof(struct pkcs7_signed_info), GFP_KERNEL);
	if (!ctx->sinfo)
		goto out_no_sinfo;
	ctx->sinfo->sig = kzalloc(sizeof(struct public_key_signature),
				  GFP_KERNEL);
	if (!ctx->sinfo->sig)
		goto out_no_sig;

	ctx->data = (unsigned long)data;
	ctx->ppcerts = &ctx->certs;
	ctx->ppsinfo = &ctx->msg->signed_infos;

	/* Attempt to decode the signature */
	ret = asn1_ber_decoder(&pkcs7_decoder, ctx, data, datalen);
	if (ret < 0) {
		msg = ERR_PTR(ret);
		goto out;
	}

	ret = pkcs7_check_authattrs(ctx->msg);
	if (ret < 0) {
		msg = ERR_PTR(ret);
		goto out;
	}

	msg = ctx->msg;
	ctx->msg = NULL;

out:
	while (ctx->certs) {
		struct x509_certificate *cert = ctx->certs;
		ctx->certs = cert->next;
		x509_free_certificate(cert);
	}
out_no_sig:
	pkcs7_free_signed_info(ctx->sinfo);
out_no_sinfo:
	pkcs7_free_message(ctx->msg);
out_no_msg:
	kfree(ctx);
out_no_ctx:
	return msg;
}
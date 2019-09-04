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
struct pkcs1pad_request {int /*<<< orphan*/  child_req; int /*<<< orphan*/  out_sg; int /*<<< orphan*/  out_buf; } ;
struct pkcs1pad_ctx {scalar_t__ key_size; int /*<<< orphan*/  child; } ;
struct crypto_akcipher {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct akcipher_request {scalar_t__ src_len; int /*<<< orphan*/  src; TYPE_1__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pkcs1pad_request* akcipher_request_ctx (struct akcipher_request*) ; 
 int /*<<< orphan*/  akcipher_request_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct akcipher_request*) ; 
 int /*<<< orphan*/  akcipher_request_set_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  akcipher_request_set_tfm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pkcs1pad_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int crypto_akcipher_decrypt (int /*<<< orphan*/ *) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 int /*<<< orphan*/  kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int pkcs1pad_decrypt_complete (struct akcipher_request*,int) ; 
 int /*<<< orphan*/  pkcs1pad_decrypt_complete_cb ; 
 int /*<<< orphan*/  pkcs1pad_sg_set_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkcs1pad_decrypt(struct akcipher_request *req)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	struct pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	int err;

	if (!ctx->key_size || req->src_len != ctx->key_size)
		return -EINVAL;

	req_ctx->out_buf = kmalloc(ctx->key_size, GFP_KERNEL);
	if (!req_ctx->out_buf)
		return -ENOMEM;

	pkcs1pad_sg_set_buf(req_ctx->out_sg, req_ctx->out_buf,
			    ctx->key_size, NULL);

	akcipher_request_set_tfm(&req_ctx->child_req, ctx->child);
	akcipher_request_set_callback(&req_ctx->child_req, req->base.flags,
			pkcs1pad_decrypt_complete_cb, req);

	/* Reuse input buffer, output to a new buffer */
	akcipher_request_set_crypt(&req_ctx->child_req, req->src,
				   req_ctx->out_sg, req->src_len,
				   ctx->key_size);

	err = crypto_akcipher_decrypt(&req_ctx->child_req);
	if (err != -EINPROGRESS && err != -EBUSY)
		return pkcs1pad_decrypt_complete(req, err);

	return err;
}
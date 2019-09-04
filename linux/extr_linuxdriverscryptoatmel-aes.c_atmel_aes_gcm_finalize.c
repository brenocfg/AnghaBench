#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct crypto_aead {int dummy; } ;
struct atmel_aes_gcm_ctx {scalar_t__ textlen; scalar_t__* tag; } ;
struct atmel_aes_dev {int flags; int /*<<< orphan*/  areq; int /*<<< orphan*/  ctx; } ;
struct aead_request {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; scalar_t__ assoclen; } ;

/* Variables and functions */
 int AES_FLAGS_GTAGEN ; 
 int /*<<< orphan*/  AES_ODATAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AES_TAGR (int /*<<< orphan*/ ) ; 
 int EBADMSG ; 
 struct aead_request* aead_request_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_complete (struct atmel_aes_dev*,int) ; 
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_is_encrypt (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_aes_read_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ crypto_memneq (scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int atmel_aes_gcm_finalize(struct atmel_aes_dev *dd)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);
	struct aead_request *req = aead_request_cast(dd->areq);
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	bool enc = atmel_aes_is_encrypt(dd);
	u32 offset, authsize, itag[4], *otag = ctx->tag;
	int err;

	/* Read the computed tag. */
	if (likely(dd->flags & AES_FLAGS_GTAGEN))
		atmel_aes_read_block(dd, AES_TAGR(0), ctx->tag);
	else
		atmel_aes_read_block(dd, AES_ODATAR(0), ctx->tag);

	offset = req->assoclen + ctx->textlen;
	authsize = crypto_aead_authsize(tfm);
	if (enc) {
		scatterwalk_map_and_copy(otag, req->dst, offset, authsize, 1);
		err = 0;
	} else {
		scatterwalk_map_and_copy(itag, req->src, offset, authsize, 0);
		err = crypto_memneq(itag, otag, authsize) ? -EBADMSG : 0;
	}

	return atmel_aes_complete(dd, err);
}
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
struct TYPE_2__ {int /*<<< orphan*/  keylen; } ;
struct atmel_aes_xts_ctx {TYPE_1__ base; int /*<<< orphan*/  key2; } ;
struct atmel_aes_reqctx {int dummy; } ;
struct atmel_aes_dev {unsigned long flags; int /*<<< orphan*/  areq; int /*<<< orphan*/  ctx; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int AES_FLAGS_ECB ; 
 int AES_FLAGS_ENCRYPT ; 
 unsigned long AES_FLAGS_MODE_MASK ; 
 int /*<<< orphan*/  AES_IDATAR (int /*<<< orphan*/ ) ; 
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 struct atmel_aes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int atmel_aes_complete (struct atmel_aes_dev*,int) ; 
 int atmel_aes_hw_init (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_aes_set_mode (struct atmel_aes_dev*,struct atmel_aes_reqctx*) ; 
 int atmel_aes_wait_for_data_ready (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write_ctrl_key (struct atmel_aes_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_aes_xts_ctx* atmel_aes_xts_ctx_cast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_xts_process_data ; 

__attribute__((used)) static int atmel_aes_xts_start(struct atmel_aes_dev *dd)
{
	struct atmel_aes_xts_ctx *ctx = atmel_aes_xts_ctx_cast(dd->ctx);
	struct ablkcipher_request *req = ablkcipher_request_cast(dd->areq);
	struct atmel_aes_reqctx *rctx = ablkcipher_request_ctx(req);
	unsigned long flags;
	int err;

	atmel_aes_set_mode(dd, rctx);

	err = atmel_aes_hw_init(dd);
	if (err)
		return atmel_aes_complete(dd, err);

	/* Compute the tweak value from req->info with ecb(aes). */
	flags = dd->flags;
	dd->flags &= ~AES_FLAGS_MODE_MASK;
	dd->flags |= (AES_FLAGS_ECB | AES_FLAGS_ENCRYPT);
	atmel_aes_write_ctrl_key(dd, false, NULL,
				 ctx->key2, ctx->base.keylen);
	dd->flags = flags;

	atmel_aes_write_block(dd, AES_IDATAR(0), req->info);
	return atmel_aes_wait_for_data_ready(dd, atmel_aes_xts_process_data);
}
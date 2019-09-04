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
struct atmel_tdes_reqctx {unsigned long mode; } ;
struct atmel_tdes_ctx {int /*<<< orphan*/  dd; void* block_size; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 void* CFB16_BLOCK_SIZE ; 
 void* CFB32_BLOCK_SIZE ; 
 void* CFB8_BLOCK_SIZE ; 
 void* DES_BLOCK_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,void*) ; 
 unsigned long TDES_FLAGS_CFB16 ; 
 unsigned long TDES_FLAGS_CFB32 ; 
 unsigned long TDES_FLAGS_CFB8 ; 
 struct atmel_tdes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int atmel_tdes_handle_queue (int /*<<< orphan*/ ,struct ablkcipher_request*) ; 
 struct atmel_tdes_ctx* crypto_ablkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int atmel_tdes_crypt(struct ablkcipher_request *req, unsigned long mode)
{
	struct atmel_tdes_ctx *ctx = crypto_ablkcipher_ctx(
			crypto_ablkcipher_reqtfm(req));
	struct atmel_tdes_reqctx *rctx = ablkcipher_request_ctx(req);

	if (mode & TDES_FLAGS_CFB8) {
		if (!IS_ALIGNED(req->nbytes, CFB8_BLOCK_SIZE)) {
			pr_err("request size is not exact amount of CFB8 blocks\n");
			return -EINVAL;
		}
		ctx->block_size = CFB8_BLOCK_SIZE;
	} else if (mode & TDES_FLAGS_CFB16) {
		if (!IS_ALIGNED(req->nbytes, CFB16_BLOCK_SIZE)) {
			pr_err("request size is not exact amount of CFB16 blocks\n");
			return -EINVAL;
		}
		ctx->block_size = CFB16_BLOCK_SIZE;
	} else if (mode & TDES_FLAGS_CFB32) {
		if (!IS_ALIGNED(req->nbytes, CFB32_BLOCK_SIZE)) {
			pr_err("request size is not exact amount of CFB32 blocks\n");
			return -EINVAL;
		}
		ctx->block_size = CFB32_BLOCK_SIZE;
	} else {
		if (!IS_ALIGNED(req->nbytes, DES_BLOCK_SIZE)) {
			pr_err("request size is not exact amount of DES blocks\n");
			return -EINVAL;
		}
		ctx->block_size = DES_BLOCK_SIZE;
	}

	rctx->mode = mode;

	return atmel_tdes_handle_queue(ctx->dd, req);
}
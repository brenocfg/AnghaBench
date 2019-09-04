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
typedef  int u32 ;
struct crypto_ahash {int dummy; } ;
struct atmel_sha_reqctx {size_t hash_size; int flags; } ;
struct atmel_sha_hmac_ctx {int* ipad; int* opad; } ;
struct atmel_sha_dev {struct ahash_request* req; } ;
struct ahash_request {int nbytes; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int ATMEL_SHA_DMA_THRESHOLD ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SHA_BCR ; 
 int /*<<< orphan*/  SHA_CR ; 
 int SHA_CR_FIRST ; 
 int SHA_CR_WUIEHV ; 
 int SHA_CR_WUIHV ; 
 int SHA_FLAGS_ALGO_MASK ; 
 int /*<<< orphan*/  SHA_MR ; 
 int SHA_MR_DUALBUFF ; 
 int SHA_MR_HMAC ; 
 int SHA_MR_MODE_AUTO ; 
 int SHA_MR_MODE_IDATAR0 ; 
 int /*<<< orphan*/  SHA_MSR ; 
 int /*<<< orphan*/  SHA_REG_DIN (size_t) ; 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int atmel_sha_complete (struct atmel_sha_dev*,int /*<<< orphan*/ ) ; 
 int atmel_sha_cpu_start (struct atmel_sha_dev*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ atmel_sha_dma_check_aligned (struct atmel_sha_dev*,int /*<<< orphan*/ ,int) ; 
 int atmel_sha_dma_start (struct atmel_sha_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_sha_hmac_final_done ; 
 int /*<<< orphan*/  atmel_sha_write (struct atmel_sha_dev*,int /*<<< orphan*/ ,int) ; 
 struct atmel_sha_hmac_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 

__attribute__((used)) static int atmel_sha_hmac_digest2(struct atmel_sha_dev *dd)
{
	struct ahash_request *req = dd->req;
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct atmel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	size_t hs = ctx->hash_size;
	size_t i, num_words = hs / sizeof(u32);
	bool use_dma = false;
	u32 mr;

	/* Special case for empty message. */
	if (!req->nbytes)
		return atmel_sha_complete(dd, -EINVAL); // TODO:

	/* Check DMA threshold and alignment. */
	if (req->nbytes > ATMEL_SHA_DMA_THRESHOLD &&
	    atmel_sha_dma_check_aligned(dd, req->src, req->nbytes))
		use_dma = true;

	/* Write both initial hash values to compute a HMAC. */
	atmel_sha_write(dd, SHA_CR, SHA_CR_WUIHV);
	for (i = 0; i < num_words; ++i)
		atmel_sha_write(dd, SHA_REG_DIN(i), hmac->ipad[i]);

	atmel_sha_write(dd, SHA_CR, SHA_CR_WUIEHV);
	for (i = 0; i < num_words; ++i)
		atmel_sha_write(dd, SHA_REG_DIN(i), hmac->opad[i]);

	/* Write the Mode, Message Size, Bytes Count then Control Registers. */
	mr = (SHA_MR_HMAC | SHA_MR_DUALBUFF);
	mr |= ctx->flags & SHA_FLAGS_ALGO_MASK;
	if (use_dma)
		mr |= SHA_MR_MODE_IDATAR0;
	else
		mr |= SHA_MR_MODE_AUTO;
	atmel_sha_write(dd, SHA_MR, mr);

	atmel_sha_write(dd, SHA_MSR, req->nbytes);
	atmel_sha_write(dd, SHA_BCR, req->nbytes);

	atmel_sha_write(dd, SHA_CR, SHA_CR_FIRST);

	/* Process data. */
	if (use_dma)
		return atmel_sha_dma_start(dd, req->src, req->nbytes,
					   atmel_sha_hmac_final_done);

	return atmel_sha_cpu_start(dd, req->src, req->nbytes, false, true,
				   atmel_sha_hmac_final_done);
}
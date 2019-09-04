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
struct stm32_hash_request_ctx {int /*<<< orphan*/  flags; } ;
struct stm32_hash_dev {scalar_t__ dma_lch; } ;
struct stm32_hash_ctx {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  HASH_FLAGS_CPU ; 
 int /*<<< orphan*/  HASH_FLAGS_FINUP ; 
 struct stm32_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 struct stm32_hash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 scalar_t__ stm32_hash_dma_aligned_data (struct ahash_request*) ; 
 int stm32_hash_final (struct ahash_request*) ; 
 struct stm32_hash_dev* stm32_hash_find_dev (struct stm32_hash_ctx*) ; 
 int stm32_hash_update (struct ahash_request*) ; 

__attribute__((used)) static int stm32_hash_finup(struct ahash_request *req)
{
	struct stm32_hash_request_ctx *rctx = ahash_request_ctx(req);
	struct stm32_hash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	struct stm32_hash_dev *hdev = stm32_hash_find_dev(ctx);
	int err1, err2;

	rctx->flags |= HASH_FLAGS_FINUP;

	if (hdev->dma_lch && stm32_hash_dma_aligned_data(req))
		rctx->flags &= ~HASH_FLAGS_CPU;

	err1 = stm32_hash_update(req);

	if (err1 == -EINPROGRESS || err1 == -EBUSY)
		return err1;

	/*
	 * final() has to be always called to cleanup resources
	 * even if update() failed, except EINPROGRESS
	 */
	err2 = stm32_hash_final(req);

	return err1 ?: err2;
}
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
struct stm32_hash_request_ctx {int /*<<< orphan*/  flags; struct stm32_hash_dev* hdev; } ;
struct stm32_hash_dev {int flags; int /*<<< orphan*/  engine; int /*<<< orphan*/  dev; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int HASH_FLAGS_CPU ; 
 int HASH_FLAGS_DMA_READY ; 
 int /*<<< orphan*/  HASH_FLAGS_ERRORS ; 
 int HASH_FLAGS_FINAL ; 
 int HASH_FLAGS_HMAC ; 
 int HASH_FLAGS_HMAC_FINAL ; 
 int HASH_FLAGS_HMAC_INIT ; 
 int HASH_FLAGS_HMAC_KEY ; 
 int HASH_FLAGS_INIT ; 
 int HASH_FLAGS_OUTPUT_READY ; 
 struct stm32_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_finalize_hash_request (int /*<<< orphan*/ ,struct ahash_request*,int) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_hash_copy_hash (struct ahash_request*) ; 
 int stm32_hash_finish (struct ahash_request*) ; 

__attribute__((used)) static void stm32_hash_finish_req(struct ahash_request *req, int err)
{
	struct stm32_hash_request_ctx *rctx = ahash_request_ctx(req);
	struct stm32_hash_dev *hdev = rctx->hdev;

	if (!err && (HASH_FLAGS_FINAL & hdev->flags)) {
		stm32_hash_copy_hash(req);
		err = stm32_hash_finish(req);
		hdev->flags &= ~(HASH_FLAGS_FINAL | HASH_FLAGS_CPU |
				 HASH_FLAGS_INIT | HASH_FLAGS_DMA_READY |
				 HASH_FLAGS_OUTPUT_READY | HASH_FLAGS_HMAC |
				 HASH_FLAGS_HMAC_INIT | HASH_FLAGS_HMAC_FINAL |
				 HASH_FLAGS_HMAC_KEY);
	} else {
		rctx->flags |= HASH_FLAGS_ERRORS;
	}

	pm_runtime_mark_last_busy(hdev->dev);
	pm_runtime_put_autosuspend(hdev->dev);

	crypto_finalize_hash_request(hdev->engine, req, err);
}
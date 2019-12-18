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
typedef  int u64 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_ctx {int cs_sequence; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/ * cs_pending; struct hl_device* hdev; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct dma_fence* ERR_PTR (int /*<<< orphan*/ ) ; 
 int HL_MAX_PENDING_CS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,int,int) ; 
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dma_fence *hl_ctx_get_fence(struct hl_ctx *ctx, u64 seq)
{
	struct hl_device *hdev = ctx->hdev;
	struct dma_fence *fence;

	spin_lock(&ctx->cs_lock);

	if (seq >= ctx->cs_sequence) {
		dev_notice(hdev->dev,
			"Can't wait on seq %llu because current CS is at seq %llu\n",
			seq, ctx->cs_sequence);
		spin_unlock(&ctx->cs_lock);
		return ERR_PTR(-EINVAL);
	}


	if (seq + HL_MAX_PENDING_CS < ctx->cs_sequence) {
		dev_dbg(hdev->dev,
			"Can't wait on seq %llu because current CS is at seq %llu (Fence is gone)\n",
			seq, ctx->cs_sequence);
		spin_unlock(&ctx->cs_lock);
		return NULL;
	}

	fence = dma_fence_get(
			ctx->cs_pending[seq & (HL_MAX_PENDING_CS - 1)]);
	spin_unlock(&ctx->cs_lock);

	return fence;
}
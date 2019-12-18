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
struct dma_fence {int dummy; } ;
struct hl_dma_fence {int submitted; int completed; int cs_seq; int sequence; struct dma_fence base_fence; int /*<<< orphan*/  lock; struct dma_fence* fence; struct hl_device* hdev; int /*<<< orphan*/  job_lock; int /*<<< orphan*/  refcount; int /*<<< orphan*/  work_tdr; int /*<<< orphan*/  job_list; struct hl_ctx* ctx; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_ctx {int cs_sequence; int /*<<< orphan*/  cs_lock; struct dma_fence** cs_pending; int /*<<< orphan*/  asid; } ;
struct hl_cs {int submitted; int completed; int cs_seq; int sequence; struct dma_fence base_fence; int /*<<< orphan*/  lock; struct dma_fence* fence; struct hl_device* hdev; int /*<<< orphan*/  job_lock; int /*<<< orphan*/  refcount; int /*<<< orphan*/  work_tdr; int /*<<< orphan*/  job_list; struct hl_ctx* ctx; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HL_MAX_PENDING_CS ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_timedout ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_init (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  hl_fence_ops ; 
 int /*<<< orphan*/  kfree (struct hl_dma_fence*) ; 
 struct hl_dma_fence* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct hl_dma_fence* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int allocate_cs(struct hl_device *hdev, struct hl_ctx *ctx,
			struct hl_cs **cs_new)
{
	struct hl_dma_fence *fence;
	struct dma_fence *other = NULL;
	struct hl_cs *cs;
	int rc;

	cs = kzalloc(sizeof(*cs), GFP_ATOMIC);
	if (!cs)
		return -ENOMEM;

	cs->ctx = ctx;
	cs->submitted = false;
	cs->completed = false;
	INIT_LIST_HEAD(&cs->job_list);
	INIT_DELAYED_WORK(&cs->work_tdr, cs_timedout);
	kref_init(&cs->refcount);
	spin_lock_init(&cs->job_lock);

	fence = kmalloc(sizeof(*fence), GFP_ATOMIC);
	if (!fence) {
		rc = -ENOMEM;
		goto free_cs;
	}

	fence->hdev = hdev;
	spin_lock_init(&fence->lock);
	cs->fence = &fence->base_fence;

	spin_lock(&ctx->cs_lock);

	fence->cs_seq = ctx->cs_sequence;
	other = ctx->cs_pending[fence->cs_seq & (HL_MAX_PENDING_CS - 1)];
	if ((other) && (!dma_fence_is_signaled(other))) {
		spin_unlock(&ctx->cs_lock);
		dev_dbg(hdev->dev,
			"Rejecting CS because of too many in-flights CS\n");
		rc = -EAGAIN;
		goto free_fence;
	}

	dma_fence_init(&fence->base_fence, &hl_fence_ops, &fence->lock,
			ctx->asid, ctx->cs_sequence);

	cs->sequence = fence->cs_seq;

	ctx->cs_pending[fence->cs_seq & (HL_MAX_PENDING_CS - 1)] =
							&fence->base_fence;
	ctx->cs_sequence++;

	dma_fence_get(&fence->base_fence);

	dma_fence_put(other);

	spin_unlock(&ctx->cs_lock);

	*cs_new = cs;

	return 0;

free_fence:
	kfree(fence);
free_cs:
	kfree(cs);
	return rc;
}
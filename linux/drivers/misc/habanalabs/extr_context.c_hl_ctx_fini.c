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
struct hl_device {struct hl_ctx* compute_ctx; scalar_t__ in_debug; } ;
struct hl_ctx {scalar_t__ asid; int /*<<< orphan*/ * cs_pending; struct hl_device* hdev; } ;

/* Variables and functions */
 scalar_t__ HL_KERNEL_ASID_ID ; 
 int HL_MAX_PENDING_CS ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_asid_free (struct hl_device*,scalar_t__) ; 
 int /*<<< orphan*/  hl_device_set_debug_mode (struct hl_device*,int) ; 
 int /*<<< orphan*/  hl_mmu_ctx_fini (struct hl_ctx*) ; 
 int /*<<< orphan*/  hl_vm_ctx_fini (struct hl_ctx*) ; 

__attribute__((used)) static void hl_ctx_fini(struct hl_ctx *ctx)
{
	struct hl_device *hdev = ctx->hdev;
	int i;

	/*
	 * If we arrived here, there are no jobs waiting for this context
	 * on its queues so we can safely remove it.
	 * This is because for each CS, we increment the ref count and for
	 * every CS that was finished we decrement it and we won't arrive
	 * to this function unless the ref count is 0
	 */

	for (i = 0 ; i < HL_MAX_PENDING_CS ; i++)
		dma_fence_put(ctx->cs_pending[i]);

	if (ctx->asid != HL_KERNEL_ASID_ID) {
		/* The engines are stopped as there is no executing CS, but the
		 * Coresight might be still working by accessing addresses
		 * related to the stopped engines. Hence stop it explicitly.
		 * Stop only if this is the compute context, as there can be
		 * only one compute context
		 */
		if ((hdev->in_debug) && (hdev->compute_ctx == ctx))
			hl_device_set_debug_mode(hdev, false);

		hl_vm_ctx_fini(ctx);
		hl_asid_free(hdev, ctx->asid);
	} else {
		hl_mmu_ctx_fini(ctx);
	}
}
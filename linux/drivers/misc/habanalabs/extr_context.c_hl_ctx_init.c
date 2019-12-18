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
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_ctx {int cs_sequence; scalar_t__ asid; scalar_t__ thread_ctx_switch_wait_token; int /*<<< orphan*/  thread_ctx_switch_token; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/  refcount; struct hl_device* hdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ HL_KERNEL_ASID_ID ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hl_asid_alloc (struct hl_device*) ; 
 int /*<<< orphan*/  hl_asid_free (struct hl_device*,scalar_t__) ; 
 int hl_mmu_ctx_init (struct hl_ctx*) ; 
 int hl_vm_ctx_init (struct hl_ctx*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hl_ctx_init(struct hl_device *hdev, struct hl_ctx *ctx, bool is_kernel_ctx)
{
	int rc = 0;

	ctx->hdev = hdev;

	kref_init(&ctx->refcount);

	ctx->cs_sequence = 1;
	spin_lock_init(&ctx->cs_lock);
	atomic_set(&ctx->thread_ctx_switch_token, 1);
	ctx->thread_ctx_switch_wait_token = 0;

	if (is_kernel_ctx) {
		ctx->asid = HL_KERNEL_ASID_ID; /* Kernel driver gets ASID 0 */
		rc = hl_mmu_ctx_init(ctx);
		if (rc) {
			dev_err(hdev->dev, "Failed to init mmu ctx module\n");
			goto mem_ctx_err;
		}
	} else {
		ctx->asid = hl_asid_alloc(hdev);
		if (!ctx->asid) {
			dev_err(hdev->dev, "No free ASID, failed to create context\n");
			return -ENOMEM;
		}

		rc = hl_vm_ctx_init(ctx);
		if (rc) {
			dev_err(hdev->dev, "Failed to init mem ctx module\n");
			rc = -ENOMEM;
			goto mem_ctx_err;
		}
	}

	return 0;

mem_ctx_err:
	if (ctx->asid != HL_KERNEL_ASID_ID)
		hl_asid_free(hdev, ctx->asid);

	return rc;
}
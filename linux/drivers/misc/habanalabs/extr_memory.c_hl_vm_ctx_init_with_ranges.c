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
typedef  int /*<<< orphan*/  u64 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct hl_ctx {int /*<<< orphan*/  mem_hash_lock; TYPE_1__ host_va_range; TYPE_1__ dram_va_range; int /*<<< orphan*/  mem_hash; int /*<<< orphan*/  asid; struct hl_device* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_va_list_locked (struct hl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_debugfs_add_ctx_mem_hash (struct hl_device*,struct hl_ctx*) ; 
 int /*<<< orphan*/  hl_mmu_ctx_fini (struct hl_ctx*) ; 
 int hl_mmu_ctx_init (struct hl_ctx*) ; 
 int hl_va_range_init (struct hl_device*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hl_vm_ctx_init_with_ranges(struct hl_ctx *ctx, u64 host_range_start,
				u64 host_range_end, u64 dram_range_start,
				u64 dram_range_end)
{
	struct hl_device *hdev = ctx->hdev;
	int rc;

	rc = hl_mmu_ctx_init(ctx);
	if (rc) {
		dev_err(hdev->dev, "failed to init context %d\n", ctx->asid);
		return rc;
	}

	mutex_init(&ctx->mem_hash_lock);
	hash_init(ctx->mem_hash);

	mutex_init(&ctx->host_va_range.lock);

	rc = hl_va_range_init(hdev, &ctx->host_va_range, host_range_start,
			host_range_end);
	if (rc) {
		dev_err(hdev->dev, "failed to init host vm range\n");
		goto host_vm_err;
	}

	mutex_init(&ctx->dram_va_range.lock);

	rc = hl_va_range_init(hdev, &ctx->dram_va_range, dram_range_start,
			dram_range_end);
	if (rc) {
		dev_err(hdev->dev, "failed to init dram vm range\n");
		goto dram_vm_err;
	}

	hl_debugfs_add_ctx_mem_hash(hdev, ctx);

	return 0;

dram_vm_err:
	mutex_destroy(&ctx->dram_va_range.lock);

	mutex_lock(&ctx->host_va_range.lock);
	clear_va_list_locked(hdev, &ctx->host_va_range.list);
	mutex_unlock(&ctx->host_va_range.lock);
host_vm_err:
	mutex_destroy(&ctx->host_va_range.lock);
	mutex_destroy(&ctx->mem_hash_lock);
	hl_mmu_ctx_fini(ctx);

	return rc;
}
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
struct hl_device {int /*<<< orphan*/  mmu_enable; } ;
struct hl_ctx {int /*<<< orphan*/  mmu_shadow_hash; int /*<<< orphan*/  mmu_phys_hash; int /*<<< orphan*/  mmu_lock; struct hl_device* hdev; } ;

/* Variables and functions */
 int dram_default_mapping_init (struct hl_ctx*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int hl_mmu_ctx_init(struct hl_ctx *ctx)
{
	struct hl_device *hdev = ctx->hdev;

	if (!hdev->mmu_enable)
		return 0;

	mutex_init(&ctx->mmu_lock);
	hash_init(ctx->mmu_phys_hash);
	hash_init(ctx->mmu_shadow_hash);

	return dram_default_mapping_init(ctx);
}
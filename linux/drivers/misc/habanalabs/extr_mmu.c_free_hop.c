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
struct pgt_info {scalar_t__ shadow_addr; int /*<<< orphan*/  node; int /*<<< orphan*/  phys_addr; } ;
typedef  struct pgt_info u64 ;
struct TYPE_2__ {int /*<<< orphan*/  mmu_hop_table_size; } ;
struct hl_device {TYPE_1__ asic_prop; int /*<<< orphan*/  mmu_pgt_pool; } ;
struct hl_ctx {struct hl_device* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pgt_info* get_pgt_info (struct hl_ctx*,struct pgt_info) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pgt_info*) ; 

__attribute__((used)) static void free_hop(struct hl_ctx *ctx, u64 hop_addr)
{
	struct hl_device *hdev = ctx->hdev;
	struct pgt_info *pgt_info = get_pgt_info(ctx, hop_addr);

	gen_pool_free(hdev->mmu_pgt_pool, pgt_info->phys_addr,
			hdev->asic_prop.mmu_hop_table_size);
	hash_del(&pgt_info->node);
	kfree((u64 *) (uintptr_t) pgt_info->shadow_addr);
	kfree(pgt_info);
}
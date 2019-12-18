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
typedef  void* u64 ;
struct pgt_info {int /*<<< orphan*/  node; scalar_t__ num_of_ptes; struct hl_ctx* ctx; void* shadow_addr; void* phys_addr; } ;
struct asic_fixed_properties {int /*<<< orphan*/  mmu_hop_table_size; } ;
struct hl_device {int /*<<< orphan*/  mmu_pgt_pool; int /*<<< orphan*/  dev; struct asic_fixed_properties asic_prop; } ;
struct hl_ctx {int /*<<< orphan*/  mmu_shadow_hash; struct hl_device* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* ULLONG_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gen_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  kfree (struct pgt_info*) ; 
 struct pgt_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 alloc_hop(struct hl_ctx *ctx)
{
	struct hl_device *hdev = ctx->hdev;
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	struct pgt_info *pgt_info;
	u64 phys_addr, shadow_addr;

	pgt_info = kmalloc(sizeof(*pgt_info), GFP_KERNEL);
	if (!pgt_info)
		return ULLONG_MAX;

	phys_addr = (u64) gen_pool_alloc(hdev->mmu_pgt_pool,
					prop->mmu_hop_table_size);
	if (!phys_addr) {
		dev_err(hdev->dev, "failed to allocate page\n");
		goto pool_add_err;
	}

	shadow_addr = (u64) (uintptr_t) kzalloc(prop->mmu_hop_table_size,
						GFP_KERNEL);
	if (!shadow_addr)
		goto shadow_err;

	pgt_info->phys_addr = phys_addr;
	pgt_info->shadow_addr = shadow_addr;
	pgt_info->ctx = ctx;
	pgt_info->num_of_ptes = 0;
	hash_add(ctx->mmu_shadow_hash, &pgt_info->node, shadow_addr);

	return shadow_addr;

shadow_err:
	gen_pool_free(hdev->mmu_pgt_pool, phys_addr, prop->mmu_hop_table_size);
pool_add_err:
	kfree(pgt_info);

	return ULLONG_MAX;
}
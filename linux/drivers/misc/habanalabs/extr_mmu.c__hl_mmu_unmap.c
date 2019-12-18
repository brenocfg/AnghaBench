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
typedef  scalar_t__ u64 ;
struct asic_fixed_properties {scalar_t__ mmu_dram_default_page_addr; int /*<<< orphan*/  va_space_dram_end_address; int /*<<< orphan*/  va_space_dram_start_address; } ;
struct hl_device {int /*<<< orphan*/  dev; scalar_t__ dram_default_page_mapping; struct asic_fixed_properties asic_prop; } ;
struct hl_ctx {struct hl_device* hdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ LAST_MASK ; 
 scalar_t__ PAGE_PRESENT_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE_2MB ; 
 scalar_t__ PTE_PHYS_ADDR_MASK ; 
 scalar_t__ ULLONG_MAX ; 
 int /*<<< orphan*/  clear_pte (struct hl_ctx*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  flush (struct hl_ctx*) ; 
 scalar_t__ get_hop0_addr (struct hl_ctx*) ; 
 scalar_t__ get_hop0_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop1_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop2_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop3_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop4_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_next_hop_addr (struct hl_ctx*,scalar_t__) ; 
 int hl_mem_area_inside_range (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ put_pte (struct hl_ctx*,scalar_t__) ; 
 int /*<<< orphan*/  write_final_pte (struct hl_ctx*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int _hl_mmu_unmap(struct hl_ctx *ctx, u64 virt_addr)
{
	struct hl_device *hdev = ctx->hdev;
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	u64 hop0_addr = 0, hop0_pte_addr = 0,
		hop1_addr = 0, hop1_pte_addr = 0,
		hop2_addr = 0, hop2_pte_addr = 0,
		hop3_addr = 0, hop3_pte_addr = 0,
		hop4_addr = 0, hop4_pte_addr = 0,
		curr_pte;
	bool is_dram_addr, is_huge, clear_hop3 = true;

	is_dram_addr = hl_mem_area_inside_range(virt_addr, PAGE_SIZE_2MB,
				prop->va_space_dram_start_address,
				prop->va_space_dram_end_address);

	hop0_addr = get_hop0_addr(ctx);
	hop0_pte_addr = get_hop0_pte_addr(ctx, hop0_addr, virt_addr);

	curr_pte = *(u64 *) (uintptr_t) hop0_pte_addr;

	hop1_addr = get_next_hop_addr(ctx, curr_pte);

	if (hop1_addr == ULLONG_MAX)
		goto not_mapped;

	hop1_pte_addr = get_hop1_pte_addr(ctx, hop1_addr, virt_addr);

	curr_pte = *(u64 *) (uintptr_t) hop1_pte_addr;

	hop2_addr = get_next_hop_addr(ctx, curr_pte);

	if (hop2_addr == ULLONG_MAX)
		goto not_mapped;

	hop2_pte_addr = get_hop2_pte_addr(ctx, hop2_addr, virt_addr);

	curr_pte = *(u64 *) (uintptr_t) hop2_pte_addr;

	hop3_addr = get_next_hop_addr(ctx, curr_pte);

	if (hop3_addr == ULLONG_MAX)
		goto not_mapped;

	hop3_pte_addr = get_hop3_pte_addr(ctx, hop3_addr, virt_addr);

	curr_pte = *(u64 *) (uintptr_t) hop3_pte_addr;

	is_huge = curr_pte & LAST_MASK;

	if (is_dram_addr && !is_huge) {
		dev_err(hdev->dev,
				"DRAM unmapping should use huge pages only\n");
		return -EFAULT;
	}

	if (!is_huge) {
		hop4_addr = get_next_hop_addr(ctx, curr_pte);

		if (hop4_addr == ULLONG_MAX)
			goto not_mapped;

		hop4_pte_addr = get_hop4_pte_addr(ctx, hop4_addr, virt_addr);

		curr_pte = *(u64 *) (uintptr_t) hop4_pte_addr;

		clear_hop3 = false;
	}

	if (hdev->dram_default_page_mapping && is_dram_addr) {
		u64 default_pte = (prop->mmu_dram_default_page_addr &
				PTE_PHYS_ADDR_MASK) | LAST_MASK |
					PAGE_PRESENT_MASK;
		if (curr_pte == default_pte) {
			dev_err(hdev->dev,
				"DRAM: hop3 PTE points to zero page, can't unmap, va: 0x%llx\n",
					virt_addr);
			goto not_mapped;
		}

		if (!(curr_pte & PAGE_PRESENT_MASK)) {
			dev_err(hdev->dev,
				"DRAM: hop3 PTE is cleared! can't unmap, va: 0x%llx\n",
					virt_addr);
			goto not_mapped;
		}

		write_final_pte(ctx, hop3_pte_addr, default_pte);
		put_pte(ctx, hop3_addr);
	} else {
		if (!(curr_pte & PAGE_PRESENT_MASK))
			goto not_mapped;

		if (hop4_addr)
			clear_pte(ctx, hop4_pte_addr);
		else
			clear_pte(ctx, hop3_pte_addr);

		if (hop4_addr && !put_pte(ctx, hop4_addr))
			clear_hop3 = true;

		if (!clear_hop3)
			goto flush;

		clear_pte(ctx, hop3_pte_addr);

		if (put_pte(ctx, hop3_addr))
			goto flush;

		clear_pte(ctx, hop2_pte_addr);

		if (put_pte(ctx, hop2_addr))
			goto flush;

		clear_pte(ctx, hop1_pte_addr);

		if (put_pte(ctx, hop1_addr))
			goto flush;

		clear_pte(ctx, hop0_pte_addr);
	}

flush:
	flush(ctx);

	return 0;

not_mapped:
	dev_err(hdev->dev, "virt addr 0x%llx is not mapped to phys addr\n",
		virt_addr);

	return -EINVAL;
}
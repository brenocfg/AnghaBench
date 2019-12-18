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
typedef  scalar_t__ u32 ;
struct asic_fixed_properties {scalar_t__ mmu_dram_default_page_addr; int /*<<< orphan*/  va_space_dram_end_address; int /*<<< orphan*/  va_space_dram_start_address; } ;
struct hl_device {int /*<<< orphan*/  dev; scalar_t__ dram_default_page_mapping; struct asic_fixed_properties asic_prop; } ;
struct hl_ctx {struct hl_device* hdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ LAST_MASK ; 
 scalar_t__ PAGE_PRESENT_MASK ; 
 scalar_t__ PAGE_SIZE_2MB ; 
 scalar_t__ PTE_PHYS_ADDR_MASK ; 
 scalar_t__ ULLONG_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  flush (struct hl_ctx*) ; 
 int /*<<< orphan*/  free_hop (struct hl_ctx*,scalar_t__) ; 
 scalar_t__ get_alloc_next_hop_addr (struct hl_ctx*,scalar_t__,int*) ; 
 scalar_t__ get_hop0_addr (struct hl_ctx*) ; 
 scalar_t__ get_hop0_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop1_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop2_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop3_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop4_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_pte (struct hl_ctx*,scalar_t__) ; 
 int hl_mem_area_inside_range (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_final_pte (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  write_pte (struct hl_ctx*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int _hl_mmu_map(struct hl_ctx *ctx, u64 virt_addr, u64 phys_addr,
		u32 page_size)
{
	struct hl_device *hdev = ctx->hdev;
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	u64 hop0_addr = 0, hop0_pte_addr = 0,
		hop1_addr = 0, hop1_pte_addr = 0,
		hop2_addr = 0, hop2_pte_addr = 0,
		hop3_addr = 0, hop3_pte_addr = 0,
		hop4_addr = 0, hop4_pte_addr = 0,
		curr_pte = 0;
	bool hop1_new = false, hop2_new = false, hop3_new = false,
		hop4_new = false, is_huge, is_dram_addr;
	int rc = -ENOMEM;

	/*
	 * This mapping function can map a 4KB/2MB page. For 2MB page there are
	 * only 3 hops rather than 4. Currently the DRAM allocation uses 2MB
	 * pages only but user memory could have been allocated with one of the
	 * two page sizes. Since this is a common code for all the three cases,
	 * we need this hugs page check.
	 */
	is_huge = page_size == PAGE_SIZE_2MB;

	is_dram_addr = hl_mem_area_inside_range(virt_addr, page_size,
				prop->va_space_dram_start_address,
				prop->va_space_dram_end_address);

	if (is_dram_addr && !is_huge) {
		dev_err(hdev->dev, "DRAM mapping should use huge pages only\n");
		return -EFAULT;
	}

	hop0_addr = get_hop0_addr(ctx);
	hop0_pte_addr = get_hop0_pte_addr(ctx, hop0_addr, virt_addr);
	curr_pte = *(u64 *) (uintptr_t) hop0_pte_addr;

	hop1_addr = get_alloc_next_hop_addr(ctx, curr_pte, &hop1_new);
	if (hop1_addr == ULLONG_MAX)
		goto err;

	hop1_pte_addr = get_hop1_pte_addr(ctx, hop1_addr, virt_addr);
	curr_pte = *(u64 *) (uintptr_t) hop1_pte_addr;

	hop2_addr = get_alloc_next_hop_addr(ctx, curr_pte, &hop2_new);
	if (hop2_addr == ULLONG_MAX)
		goto err;

	hop2_pte_addr = get_hop2_pte_addr(ctx, hop2_addr, virt_addr);
	curr_pte = *(u64 *) (uintptr_t) hop2_pte_addr;

	hop3_addr = get_alloc_next_hop_addr(ctx, curr_pte, &hop3_new);
	if (hop3_addr == ULLONG_MAX)
		goto err;

	hop3_pte_addr = get_hop3_pte_addr(ctx, hop3_addr, virt_addr);
	curr_pte = *(u64 *) (uintptr_t) hop3_pte_addr;

	if (!is_huge) {
		hop4_addr = get_alloc_next_hop_addr(ctx, curr_pte, &hop4_new);
		if (hop4_addr == ULLONG_MAX)
			goto err;

		hop4_pte_addr = get_hop4_pte_addr(ctx, hop4_addr, virt_addr);
		curr_pte = *(u64 *) (uintptr_t) hop4_pte_addr;
	}

	if (hdev->dram_default_page_mapping && is_dram_addr) {
		u64 default_pte = (prop->mmu_dram_default_page_addr &
					PTE_PHYS_ADDR_MASK) | LAST_MASK |
						PAGE_PRESENT_MASK;

		if (curr_pte != default_pte) {
			dev_err(hdev->dev,
				"DRAM: mapping already exists for virt_addr 0x%llx\n",
					virt_addr);
			rc = -EINVAL;
			goto err;
		}

		if (hop1_new || hop2_new || hop3_new || hop4_new) {
			dev_err(hdev->dev,
				"DRAM mapping should not allocate more hops\n");
			rc = -EFAULT;
			goto err;
		}
	} else if (curr_pte & PAGE_PRESENT_MASK) {
		dev_err(hdev->dev,
			"mapping already exists for virt_addr 0x%llx\n",
				virt_addr);

		dev_dbg(hdev->dev, "hop0 pte: 0x%llx (0x%llx)\n",
			*(u64 *) (uintptr_t) hop0_pte_addr, hop0_pte_addr);
		dev_dbg(hdev->dev, "hop1 pte: 0x%llx (0x%llx)\n",
			*(u64 *) (uintptr_t) hop1_pte_addr, hop1_pte_addr);
		dev_dbg(hdev->dev, "hop2 pte: 0x%llx (0x%llx)\n",
			*(u64 *) (uintptr_t) hop2_pte_addr, hop2_pte_addr);
		dev_dbg(hdev->dev, "hop3 pte: 0x%llx (0x%llx)\n",
			*(u64 *) (uintptr_t) hop3_pte_addr, hop3_pte_addr);

		if (!is_huge)
			dev_dbg(hdev->dev, "hop4 pte: 0x%llx (0x%llx)\n",
				*(u64 *) (uintptr_t) hop4_pte_addr,
				hop4_pte_addr);

		rc = -EINVAL;
		goto err;
	}

	curr_pte = (phys_addr & PTE_PHYS_ADDR_MASK) | LAST_MASK
			| PAGE_PRESENT_MASK;

	if (is_huge)
		write_final_pte(ctx, hop3_pte_addr, curr_pte);
	else
		write_final_pte(ctx, hop4_pte_addr, curr_pte);

	if (hop1_new) {
		curr_pte =
			(hop1_addr & PTE_PHYS_ADDR_MASK) | PAGE_PRESENT_MASK;
		write_pte(ctx, hop0_pte_addr, curr_pte);
	}
	if (hop2_new) {
		curr_pte =
			(hop2_addr & PTE_PHYS_ADDR_MASK) | PAGE_PRESENT_MASK;
		write_pte(ctx, hop1_pte_addr, curr_pte);
		get_pte(ctx, hop1_addr);
	}
	if (hop3_new) {
		curr_pte =
			(hop3_addr & PTE_PHYS_ADDR_MASK) | PAGE_PRESENT_MASK;
		write_pte(ctx, hop2_pte_addr, curr_pte);
		get_pte(ctx, hop2_addr);
	}

	if (!is_huge) {
		if (hop4_new) {
			curr_pte = (hop4_addr & PTE_PHYS_ADDR_MASK) |
					PAGE_PRESENT_MASK;
			write_pte(ctx, hop3_pte_addr, curr_pte);
			get_pte(ctx, hop3_addr);
		}

		get_pte(ctx, hop4_addr);
	} else {
		get_pte(ctx, hop3_addr);
	}

	flush(ctx);

	return 0;

err:
	if (hop4_new)
		free_hop(ctx, hop4_addr);
	if (hop3_new)
		free_hop(ctx, hop3_addr);
	if (hop2_new)
		free_hop(ctx, hop2_addr);
	if (hop1_new)
		free_hop(ctx, hop1_addr);

	return rc;
}
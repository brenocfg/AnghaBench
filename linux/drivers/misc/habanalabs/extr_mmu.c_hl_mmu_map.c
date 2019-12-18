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
typedef  int u32 ;
struct hl_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mmu_enable; } ;
struct hl_ctx {struct hl_device* hdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int PAGE_SIZE_2MB ; 
 int PAGE_SIZE_4KB ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,int) ; 
 int _hl_mmu_map (struct hl_ctx*,int,int,int) ; 
 scalar_t__ _hl_mmu_unmap (struct hl_ctx*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int) ; 

int hl_mmu_map(struct hl_ctx *ctx, u64 virt_addr, u64 phys_addr, u32 page_size)
{
	struct hl_device *hdev = ctx->hdev;
	u64 real_virt_addr, real_phys_addr;
	u32 real_page_size, npages;
	int i, rc, mapped_cnt = 0;

	if (!hdev->mmu_enable)
		return 0;

	/*
	 * The H/W handles mapping of 4KB/2MB page. Hence if the host page size
	 * is bigger, we break it to sub-pages and map them separately.
	 */
	if ((page_size % PAGE_SIZE_2MB) == 0) {
		real_page_size = PAGE_SIZE_2MB;
	} else if ((page_size % PAGE_SIZE_4KB) == 0) {
		real_page_size = PAGE_SIZE_4KB;
	} else {
		dev_err(hdev->dev,
			"page size of %u is not 4KB nor 2MB aligned, can't map\n",
				page_size);

		return -EFAULT;
	}

	WARN_ONCE((phys_addr & (real_page_size - 1)),
		"Mapping 0x%llx with page size of 0x%x is erroneous! Address must be divisible by page size",
		phys_addr, real_page_size);

	npages = page_size / real_page_size;
	real_virt_addr = virt_addr;
	real_phys_addr = phys_addr;

	for (i = 0 ; i < npages ; i++) {
		rc = _hl_mmu_map(ctx, real_virt_addr, real_phys_addr,
				real_page_size);
		if (rc)
			goto err;

		real_virt_addr += real_page_size;
		real_phys_addr += real_page_size;
		mapped_cnt++;
	}

	return 0;

err:
	real_virt_addr = virt_addr;
	for (i = 0 ; i < mapped_cnt ; i++) {
		if (_hl_mmu_unmap(ctx, real_virt_addr))
			dev_warn_ratelimited(hdev->dev,
				"failed to unmap va: 0x%llx\n", real_virt_addr);

		real_virt_addr += real_page_size;
	}

	return rc;
}
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
typedef  size_t u64 ;
typedef  scalar_t__ u32 ;
struct hl_vm_phys_pg_pack {size_t npages; size_t* pages; int /*<<< orphan*/  handle; scalar_t__ page_size; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_ctx {struct hl_device* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t,scalar_t__) ; 
 int hl_mmu_map (struct hl_ctx*,size_t,size_t,scalar_t__) ; 
 scalar_t__ hl_mmu_unmap (struct hl_ctx*,size_t,scalar_t__) ; 

__attribute__((used)) static int map_phys_page_pack(struct hl_ctx *ctx, u64 vaddr,
		struct hl_vm_phys_pg_pack *phys_pg_pack)
{
	struct hl_device *hdev = ctx->hdev;
	u64 next_vaddr = vaddr, paddr, mapped_pg_cnt = 0, i;
	u32 page_size = phys_pg_pack->page_size;
	int rc = 0;

	for (i = 0 ; i < phys_pg_pack->npages ; i++) {
		paddr = phys_pg_pack->pages[i];

		rc = hl_mmu_map(ctx, next_vaddr, paddr, page_size);
		if (rc) {
			dev_err(hdev->dev,
				"map failed for handle %u, npages: %llu, mapped: %llu",
				phys_pg_pack->handle, phys_pg_pack->npages,
				mapped_pg_cnt);
			goto err;
		}

		mapped_pg_cnt++;
		next_vaddr += page_size;
	}

	return 0;

err:
	next_vaddr = vaddr;
	for (i = 0 ; i < mapped_pg_cnt ; i++) {
		if (hl_mmu_unmap(ctx, next_vaddr, page_size))
			dev_warn_ratelimited(hdev->dev,
				"failed to unmap handle %u, va: 0x%llx, pa: 0x%llx, page size: %u\n",
					phys_pg_pack->handle, next_vaddr,
					phys_pg_pack->pages[i], page_size);

		next_vaddr += page_size;
	}

	return rc;
}
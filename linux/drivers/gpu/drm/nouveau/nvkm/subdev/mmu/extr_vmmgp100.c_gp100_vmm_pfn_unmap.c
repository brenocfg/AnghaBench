#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_vmm {TYPE_3__* mmu; } ;
struct nvkm_mmu_pt {int /*<<< orphan*/  memory; scalar_t__ base; } ;
struct device {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__ subdev; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 
 int nvkm_ro32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
gp100_vmm_pfn_unmap(struct nvkm_vmm *vmm,
		    struct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	struct device *dev = vmm->mmu->subdev.device->dev;
	dma_addr_t addr;

	nvkm_kmap(pt->memory);
	while (ptes--) {
		u32 datalo = nvkm_ro32(pt->memory, pt->base + ptei * 8 + 0);
		u32 datahi = nvkm_ro32(pt->memory, pt->base + ptei * 8 + 4);
		u64 data   = (u64)datahi << 32 | datalo;
		if ((data & (3ULL << 1)) != 0) {
			addr = (data >> 8) << 12;
			dma_unmap_page(dev, addr, PAGE_SIZE, DMA_BIDIRECTIONAL);
		}
		ptei++;
	}
	nvkm_done(pt->memory);
}
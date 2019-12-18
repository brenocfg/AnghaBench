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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__* cpu; } ;
struct lima_vm {TYPE_3__* bts; TYPE_2__ pd; TYPE_1__* dev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {scalar_t__ dma; scalar_t__* cpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 scalar_t__ LIMA_BTE (scalar_t__) ; 
 scalar_t__ LIMA_PAGE_SIZE ; 
 scalar_t__ LIMA_PBE (scalar_t__) ; 
 scalar_t__ LIMA_VM_FLAGS_CACHE ; 
 scalar_t__ LIMA_VM_FLAG_PRESENT ; 
 int LIMA_VM_NUM_PT_PER_BT ; 
 scalar_t__ LIMA_VM_NUM_PT_PER_BT_SHIFT ; 
 int __GFP_ZERO ; 
 scalar_t__* dma_alloc_wc (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  lima_vm_unmap_page_table (struct lima_vm*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int lima_vm_map_page_table(struct lima_vm *vm, dma_addr_t *dma,
				  u32 start, u32 end)
{
	u64 addr;
	int i = 0;

	for (addr = start; addr <= end; addr += LIMA_PAGE_SIZE) {
		u32 pbe = LIMA_PBE(addr);
		u32 bte = LIMA_BTE(addr);

		if (!vm->bts[pbe].cpu) {
			dma_addr_t pts;
			u32 *pd;
			int j;

			vm->bts[pbe].cpu = dma_alloc_wc(
				vm->dev->dev, LIMA_PAGE_SIZE << LIMA_VM_NUM_PT_PER_BT_SHIFT,
				&vm->bts[pbe].dma, GFP_KERNEL | __GFP_ZERO);
			if (!vm->bts[pbe].cpu) {
				if (addr != start)
					lima_vm_unmap_page_table(vm, start, addr - 1);
				return -ENOMEM;
			}

			pts = vm->bts[pbe].dma;
			pd = vm->pd.cpu + (pbe << LIMA_VM_NUM_PT_PER_BT_SHIFT);
			for (j = 0; j < LIMA_VM_NUM_PT_PER_BT; j++) {
				pd[j] = pts | LIMA_VM_FLAG_PRESENT;
				pts += LIMA_PAGE_SIZE;
			}
		}

		vm->bts[pbe].cpu[bte] = dma[i++] | LIMA_VM_FLAGS_CACHE;
	}

	return 0;
}
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
typedef  scalar_t__ u32 ;
struct lima_vm {TYPE_1__* bts; } ;
struct TYPE_2__ {scalar_t__* cpu; } ;

/* Variables and functions */
 scalar_t__ LIMA_BTE (scalar_t__) ; 
 scalar_t__ LIMA_PAGE_SIZE ; 
 scalar_t__ LIMA_PBE (scalar_t__) ; 

__attribute__((used)) static void lima_vm_unmap_page_table(struct lima_vm *vm, u32 start, u32 end)
{
	u32 addr;

	for (addr = start; addr <= end; addr += LIMA_PAGE_SIZE) {
		u32 pbe = LIMA_PBE(addr);
		u32 bte = LIMA_BTE(addr);

		vm->bts[pbe].cpu[bte] = 0;
	}
}
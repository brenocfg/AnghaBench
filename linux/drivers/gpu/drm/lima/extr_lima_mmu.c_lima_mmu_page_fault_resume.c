#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct lima_ip {struct lima_device* dev; } ;
struct lima_device {TYPE_2__* empty_vm; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int dma; } ;
struct TYPE_4__ {TYPE_1__ pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_MMU_COMMAND_ENABLE_PAGING ; 
 int /*<<< orphan*/  LIMA_MMU_COMMAND_HARD_RESET ; 
 int /*<<< orphan*/  LIMA_MMU_DTE_ADDR ; 
 int /*<<< orphan*/  LIMA_MMU_INT_MASK ; 
 int LIMA_MMU_INT_PAGE_FAULT ; 
 int LIMA_MMU_INT_READ_BUS_ERROR ; 
 int /*<<< orphan*/  LIMA_MMU_STATUS ; 
 int LIMA_MMU_STATUS_PAGE_FAULT_ACTIVE ; 
 int LIMA_MMU_STATUS_PAGING_ENABLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lima_mmu_send_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int mmu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_write (int /*<<< orphan*/ ,int) ; 

void lima_mmu_page_fault_resume(struct lima_ip *ip)
{
	struct lima_device *dev = ip->dev;
	u32 status = mmu_read(LIMA_MMU_STATUS);
	u32 v;

	if (status & LIMA_MMU_STATUS_PAGE_FAULT_ACTIVE) {
		dev_info(dev->dev, "mmu resume\n");

		mmu_write(LIMA_MMU_INT_MASK, 0);
		mmu_write(LIMA_MMU_DTE_ADDR, 0xCAFEBABE);
		lima_mmu_send_command(LIMA_MMU_COMMAND_HARD_RESET,
				      LIMA_MMU_DTE_ADDR, v, v == 0);
		mmu_write(LIMA_MMU_INT_MASK, LIMA_MMU_INT_PAGE_FAULT | LIMA_MMU_INT_READ_BUS_ERROR);
		mmu_write(LIMA_MMU_DTE_ADDR, dev->empty_vm->pd.dma);
		lima_mmu_send_command(LIMA_MMU_COMMAND_ENABLE_PAGING,
				      LIMA_MMU_STATUS, v,
				      v & LIMA_MMU_STATUS_PAGING_ENABLED);
	}
}
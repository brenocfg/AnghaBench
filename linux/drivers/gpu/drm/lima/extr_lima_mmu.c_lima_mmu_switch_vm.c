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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;
struct lima_vm {TYPE_1__ pd; } ;
struct lima_ip {struct lima_device* dev; } ;
struct lima_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_MMU_COMMAND ; 
 int /*<<< orphan*/  LIMA_MMU_COMMAND_DISABLE_STALL ; 
 int /*<<< orphan*/  LIMA_MMU_COMMAND_ENABLE_STALL ; 
 int /*<<< orphan*/  LIMA_MMU_COMMAND_ZAP_CACHE ; 
 int /*<<< orphan*/  LIMA_MMU_DTE_ADDR ; 
 int /*<<< orphan*/  LIMA_MMU_STATUS ; 
 int LIMA_MMU_STATUS_STALL_ACTIVE ; 
 int /*<<< orphan*/  lima_mmu_send_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mmu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lima_mmu_switch_vm(struct lima_ip *ip, struct lima_vm *vm)
{
	struct lima_device *dev = ip->dev;
	u32 v;

	lima_mmu_send_command(LIMA_MMU_COMMAND_ENABLE_STALL,
			      LIMA_MMU_STATUS, v,
			      v & LIMA_MMU_STATUS_STALL_ACTIVE);

	if (vm)
		mmu_write(LIMA_MMU_DTE_ADDR, vm->pd.dma);

	/* flush the TLB */
	mmu_write(LIMA_MMU_COMMAND, LIMA_MMU_COMMAND_ZAP_CACHE);

	lima_mmu_send_command(LIMA_MMU_COMMAND_DISABLE_STALL,
			      LIMA_MMU_STATUS, v,
			      !(v & LIMA_MMU_STATUS_STALL_ACTIVE));
}
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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {size_t num_blocks; TYPE_1__* fw_mon; } ;
struct iwl_trans {TYPE_2__ dbg; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  physical; void* block; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_trans*,char*,scalar_t__) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int __GFP_NOWARN ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void iwl_pcie_alloc_fw_monitor_block(struct iwl_trans *trans,
					    u8 max_power, u8 min_power)
{
	void *cpu_addr = NULL;
	dma_addr_t phys = 0;
	u32 size = 0;
	u8 power;

	for (power = max_power; power >= min_power; power--) {
		size = BIT(power);
		cpu_addr = dma_alloc_coherent(trans->dev, size, &phys,
					      GFP_KERNEL | __GFP_NOWARN);
		if (!cpu_addr)
			continue;

		IWL_INFO(trans,
			 "Allocated 0x%08x bytes for firmware monitor.\n",
			 size);
		break;
	}

	if (WARN_ON_ONCE(!cpu_addr))
		return;

	if (power != max_power)
		IWL_ERR(trans,
			"Sorry - debug buffer is only %luK while you requested %luK\n",
			(unsigned long)BIT(power - 10),
			(unsigned long)BIT(max_power - 10));

	trans->dbg.fw_mon[trans->dbg.num_blocks].block = cpu_addr;
	trans->dbg.fw_mon[trans->dbg.num_blocks].physical = phys;
	trans->dbg.fw_mon[trans->dbg.num_blocks].size = size;
	trans->dbg.num_blocks++;
}
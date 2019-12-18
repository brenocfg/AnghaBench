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
struct TYPE_4__ {int num_blocks; TYPE_1__* fw_mon; } ;
struct iwl_trans {TYPE_2__ dbg; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ physical; int /*<<< orphan*/ * block; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void iwl_pcie_free_fw_monitor(struct iwl_trans *trans)
{
	int i;

	for (i = 0; i < trans->dbg.num_blocks; i++) {
		dma_free_coherent(trans->dev, trans->dbg.fw_mon[i].size,
				  trans->dbg.fw_mon[i].block,
				  trans->dbg.fw_mon[i].physical);
		trans->dbg.fw_mon[i].block = NULL;
		trans->dbg.fw_mon[i].physical = 0;
		trans->dbg.fw_mon[i].size = 0;
		trans->dbg.num_blocks--;
	}
}
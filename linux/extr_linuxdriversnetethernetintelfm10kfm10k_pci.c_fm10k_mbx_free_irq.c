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
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disconnect ) (struct fm10k_hw*,TYPE_3__*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; TYPE_3__ mbx; } ;
struct fm10k_intfc {struct msix_entry* msix_entries; struct fm10k_hw hw; } ;

/* Variables and functions */
 int FM10K_EIMR ; 
 int FM10K_EIMR_DISABLE (int /*<<< orphan*/ ) ; 
 int FM10K_ITR (size_t) ; 
 int FM10K_ITR_MASK_SET ; 
 size_t FM10K_MBX_VECTOR ; 
 int FM10K_VFITR (size_t) ; 
 int /*<<< orphan*/  FUM_FAULT ; 
 int /*<<< orphan*/  MAILBOX ; 
 int /*<<< orphan*/  MAXHOLDTIME ; 
 int /*<<< orphan*/  PCA_FAULT ; 
 int /*<<< orphan*/  SRAMERROR ; 
 int /*<<< orphan*/  SWITCHNOTREADY ; 
 int /*<<< orphan*/  SWITCHREADY ; 
 int /*<<< orphan*/  VFLR ; 
 scalar_t__ fm10k_mac_pf ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fm10k_intfc*) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,TYPE_3__*) ; 

void fm10k_mbx_free_irq(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;
	struct msix_entry *entry;
	int itr_reg;

	/* no mailbox IRQ to free if MSI-X is not enabled */
	if (!interface->msix_entries)
		return;

	entry = &interface->msix_entries[FM10K_MBX_VECTOR];

	/* disconnect the mailbox */
	hw->mbx.ops.disconnect(hw, &hw->mbx);

	/* disable Mailbox cause */
	if (hw->mac.type == fm10k_mac_pf) {
		fm10k_write_reg(hw, FM10K_EIMR,
				FM10K_EIMR_DISABLE(PCA_FAULT) |
				FM10K_EIMR_DISABLE(FUM_FAULT) |
				FM10K_EIMR_DISABLE(MAILBOX) |
				FM10K_EIMR_DISABLE(SWITCHREADY) |
				FM10K_EIMR_DISABLE(SWITCHNOTREADY) |
				FM10K_EIMR_DISABLE(SRAMERROR) |
				FM10K_EIMR_DISABLE(VFLR) |
				FM10K_EIMR_DISABLE(MAXHOLDTIME));
		itr_reg = FM10K_ITR(FM10K_MBX_VECTOR);
	} else {
		itr_reg = FM10K_VFITR(FM10K_MBX_VECTOR);
	}

	fm10k_write_reg(hw, itr_reg, FM10K_ITR_MASK_SET);

	free_irq(entry->vector, interface);
}
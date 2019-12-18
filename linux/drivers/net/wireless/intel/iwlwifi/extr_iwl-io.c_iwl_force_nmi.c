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
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_SET_NMI_REG ; 
 int /*<<< orphan*/  DEVICE_SET_NMI_VAL_DRV ; 
 scalar_t__ IWL_DEVICE_FAMILY_9000 ; 
 scalar_t__ IWL_DEVICE_FAMILY_AX210 ; 
 int /*<<< orphan*/  UREG_DOORBELL_TO_ISR6 ; 
 int /*<<< orphan*/  UREG_DOORBELL_TO_ISR6_NMI_BIT ; 
 int /*<<< orphan*/  UREG_NIC_SET_NMI_DRIVER ; 
 int /*<<< orphan*/  UREG_NIC_SET_NMI_DRIVER_NMI_FROM_DRIVER_MSK ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_umac_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwl_force_nmi(struct iwl_trans *trans)
{
	if (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_9000)
		iwl_write_prph(trans, DEVICE_SET_NMI_REG,
			       DEVICE_SET_NMI_VAL_DRV);
	else if (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210)
		iwl_write_umac_prph(trans, UREG_NIC_SET_NMI_DRIVER,
				UREG_NIC_SET_NMI_DRIVER_NMI_FROM_DRIVER_MSK);
	else
		iwl_write_umac_prph(trans, UREG_DOORBELL_TO_ISR6,
				    UREG_DOORBELL_TO_ISR6_NMI_BIT);
}
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
typedef  scalar_t__ u32 ;
struct iwl_mvm {TYPE_3__* trans; } ;
struct TYPE_6__ {TYPE_2__* cfg; TYPE_1__* trans_cfg; } ;
struct TYPE_5__ {scalar_t__ gp2_reg_addr; } ;
struct TYPE_4__ {scalar_t__ device_family; } ;

/* Variables and functions */
 scalar_t__ DEVICE_SYSTEM_TIME_REG ; 
 scalar_t__ IWL_DEVICE_FAMILY_22000 ; 
 scalar_t__ iwl_read_prph (TYPE_3__*,scalar_t__) ; 

u32 iwl_mvm_get_systime(struct iwl_mvm *mvm)
{
	u32 reg_addr = DEVICE_SYSTEM_TIME_REG;

	if (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22000 &&
	    mvm->trans->cfg->gp2_reg_addr)
		reg_addr = mvm->trans->cfg->gp2_reg_addr;

	return iwl_read_prph(mvm->trans, reg_addr);
}
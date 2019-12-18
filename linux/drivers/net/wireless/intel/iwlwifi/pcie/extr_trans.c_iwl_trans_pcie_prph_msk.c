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
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 scalar_t__ IWL_DEVICE_FAMILY_22560 ; 

__attribute__((used)) static u32 iwl_trans_pcie_prph_msk(struct iwl_trans *trans)
{
	if (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22560)
		return 0x00FFFFFF;
	else
		return 0x000FFFFF;
}
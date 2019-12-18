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
struct TYPE_3__ {TYPE_2__* entry; } ;
struct vega20_smumgr {TYPE_1__ smu_tables; } ;
struct pp_hwmgr {scalar_t__ smu_backend; } ;
struct TYPE_4__ {scalar_t__ mc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetToolsDramAddrHigh ; 
 int /*<<< orphan*/  PPSMC_MSG_SetToolsDramAddrLow ; 
 size_t TABLE_PMSTATUSLOG ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 
 int vega20_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_set_tools_address(struct pp_hwmgr *hwmgr)
{
	struct vega20_smumgr *priv =
			(struct vega20_smumgr *)(hwmgr->smu_backend);
	int ret = 0;

	if (priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr) {
		ret = vega20_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetToolsDramAddrHigh,
				upper_32_bits(priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr));
		if (!ret)
			ret = vega20_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetToolsDramAddrLow,
					lower_32_bits(priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr));
	}

	return ret;
}
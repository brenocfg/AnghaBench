#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int PPSMC_MSG_DisableSmuFeatures ; 
 int PPSMC_MSG_EnableSmuFeatures ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int,int /*<<< orphan*/ ) ; 

int vega10_enable_smc_features(struct pp_hwmgr *hwmgr,
			       bool enable, uint32_t feature_mask)
{
	int msg = enable ? PPSMC_MSG_EnableSmuFeatures :
			PPSMC_MSG_DisableSmuFeatures;

	return smum_send_msg_to_smc_with_parameter(hwmgr,
			msg, feature_mask);
}
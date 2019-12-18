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
struct TYPE_2__ {int /*<<< orphan*/  soft_max_clk; } ;
struct smu8_hwmgr {TYPE_1__ sclk_dpm; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetWatermarkFrequency ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_set_watermark_threshold(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data =
				  hwmgr->backend;

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetWatermarkFrequency,
					data->sclk_dpm.soft_max_clk);

	return 0;
}
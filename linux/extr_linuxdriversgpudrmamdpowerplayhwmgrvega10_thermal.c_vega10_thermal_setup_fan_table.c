#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
struct TYPE_10__ {int FanPwmMin; int /*<<< orphan*/  FanStartTemp; int /*<<< orphan*/  FanStopTemp; int /*<<< orphan*/  FanZeroRpmEnable; int /*<<< orphan*/  FanGainHbm; int /*<<< orphan*/  FanGainPlx; int /*<<< orphan*/  FanGainVrMvdd; int /*<<< orphan*/  FanGainVrVddc; int /*<<< orphan*/  FanGainLiquid; int /*<<< orphan*/  FanGainHotspot; int /*<<< orphan*/  FanGainEdge; void* FanTargetGfxclk; scalar_t__ FanTargetTemperature; void* FanAcousticLimitRpm; int /*<<< orphan*/  FanThrottlingRpm; void* FanMaximumRpm; } ;
struct TYPE_9__ {TYPE_5__ pp_table; } ;
struct vega10_hwmgr {TYPE_4__ smc_state_table; TYPE_1__* smu_features; } ;
struct TYPE_7__ {int usPWMMin; int /*<<< orphan*/  usZeroRPMStartTemperature; int /*<<< orphan*/  usZeroRPMStopTemperature; int /*<<< orphan*/  ucEnableZeroRPM; int /*<<< orphan*/  usFanGainHbm; int /*<<< orphan*/  usFanGainPlx; int /*<<< orphan*/  usFanGainVrMvdd; int /*<<< orphan*/  usFanGainVrVddc; int /*<<< orphan*/  usFanGainLiquid; int /*<<< orphan*/  usFanGainHotspot; int /*<<< orphan*/  usFanGainEdge; scalar_t__ ulTargetGfxClk; scalar_t__ usTMax; scalar_t__ ulMinFanSCLKAcousticLimit; int /*<<< orphan*/  usFanRPMMaxLimit; scalar_t__ usMaxFanRPM; } ;
struct TYPE_8__ {TYPE_2__ advanceFanControlParameters; } ;
struct pp_hwmgr {TYPE_3__ thermal_controller; struct vega10_hwmgr* backend; } ;
struct TYPE_6__ {int /*<<< orphan*/  supported; } ;
typedef  TYPE_5__ PPTable_t ;

/* Variables and functions */
 size_t GNLD_FAN_CONTROL ; 
 int /*<<< orphan*/  PPSMC_MSG_SetFanTemperatureTarget ; 
 int /*<<< orphan*/  PPTABLE ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smum_smc_table_manager (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int vega10_thermal_setup_fan_table(struct pp_hwmgr *hwmgr)
{
	int ret;
	struct vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *table = &(data->smc_state_table.pp_table);

	if (!data->smu_features[GNLD_FAN_CONTROL].supported)
		return 0;

	table->FanMaximumRpm = (uint16_t)hwmgr->thermal_controller.
			advanceFanControlParameters.usMaxFanRPM;
	table->FanThrottlingRpm = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanRPMMaxLimit;
	table->FanAcousticLimitRpm = (uint16_t)(hwmgr->thermal_controller.
			advanceFanControlParameters.ulMinFanSCLKAcousticLimit);
	table->FanTargetTemperature = hwmgr->thermal_controller.
			advanceFanControlParameters.usTMax;

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetFanTemperatureTarget,
				(uint32_t)table->FanTargetTemperature);

	table->FanPwmMin = hwmgr->thermal_controller.
			advanceFanControlParameters.usPWMMin * 255 / 100;
	table->FanTargetGfxclk = (uint16_t)(hwmgr->thermal_controller.
			advanceFanControlParameters.ulTargetGfxClk);
	table->FanGainEdge = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainEdge;
	table->FanGainHotspot = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainHotspot;
	table->FanGainLiquid = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainLiquid;
	table->FanGainVrVddc = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainVrVddc;
	table->FanGainVrMvdd = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainVrMvdd;
	table->FanGainPlx = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainPlx;
	table->FanGainHbm = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainHbm;
	table->FanZeroRpmEnable = hwmgr->thermal_controller.
			advanceFanControlParameters.ucEnableZeroRPM;
	table->FanStopTemp = hwmgr->thermal_controller.
			advanceFanControlParameters.usZeroRPMStopTemperature;
	table->FanStartTemp = hwmgr->thermal_controller.
			advanceFanControlParameters.usZeroRPMStartTemperature;

	ret = smum_smc_table_manager(hwmgr,
				(uint8_t *)(&(data->smc_state_table.pp_table)),
				PPTABLE, false);
	if (ret)
		pr_info("Failed to update Fan Control Table in PPTable!");

	return ret;
}
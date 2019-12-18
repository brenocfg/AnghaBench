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
typedef  int /*<<< orphan*/  uint8_t ;
struct smu_table_context {TYPE_3__* driver_pptable; } ;
struct smu_context {struct smu_table_context smu_table; } ;
struct atom_smc_dpm_info_v4_4 {TYPE_2__* i2ccontrollers; int /*<<< orphan*/  fllgfxclkspreadfreq; int /*<<< orphan*/  fllgfxclkspreadpercent; int /*<<< orphan*/  fllgfxclkspreadenabled; int /*<<< orphan*/  fclkspreadfreq; int /*<<< orphan*/  fclkspreadpercent; int /*<<< orphan*/  fclkspreadenabled; int /*<<< orphan*/  uclkspreadfreq; int /*<<< orphan*/  uclkspreadpercent; int /*<<< orphan*/  pllgfxclkspreadfreq; int /*<<< orphan*/  pllgfxclkspreadpercent; int /*<<< orphan*/  pllgfxclkspreadenabled; int /*<<< orphan*/  ledpin2; int /*<<< orphan*/  ledpin1; int /*<<< orphan*/  ledpin0; int /*<<< orphan*/  padding2; int /*<<< orphan*/  padding1; int /*<<< orphan*/  vr1hotpolarity; int /*<<< orphan*/  vr1hotgpio; int /*<<< orphan*/  vr0hotpolarity; int /*<<< orphan*/  vr0hotgpio; int /*<<< orphan*/  acdcpolarity; int /*<<< orphan*/  acdcgpio; int /*<<< orphan*/  padding_telemetrymem1; int /*<<< orphan*/  mem1offset; int /*<<< orphan*/  mem1maxcurrent; int /*<<< orphan*/  padding_telemetrymem0; int /*<<< orphan*/  mem0offset; int /*<<< orphan*/  mem0maxcurrent; int /*<<< orphan*/  padding_telemetrysoc; int /*<<< orphan*/  socoffset; int /*<<< orphan*/  socmaxcurrent; int /*<<< orphan*/  padding_telemetrygfx; int /*<<< orphan*/  gfxoffset; int /*<<< orphan*/  gfxmaxcurrent; int /*<<< orphan*/  externalsensorpresent; int /*<<< orphan*/  soculvphasesheddingmask; int /*<<< orphan*/  gfxulvphasesheddingmask; int /*<<< orphan*/  vddmem1vrmapping; int /*<<< orphan*/  vddmem0vrmapping; int /*<<< orphan*/  vddsocvrmapping; int /*<<< orphan*/  vddgfxvrmapping; int /*<<< orphan*/  maxvoltagestepsoc; int /*<<< orphan*/  maxvoltagestepgfx; } ;
struct TYPE_6__ {TYPE_1__* I2cControllers; int /*<<< orphan*/  FllGfxclkSpreadFreq; int /*<<< orphan*/  FllGfxclkSpreadPercent; int /*<<< orphan*/  FllGfxclkSpreadEnabled; int /*<<< orphan*/  FclkSpreadFreq; int /*<<< orphan*/  FclkSpreadPercent; int /*<<< orphan*/  FclkSpreadEnabled; int /*<<< orphan*/  UclkSpreadFreq; int /*<<< orphan*/  UclkSpreadPercent; scalar_t__ UclkSpreadEnabled; int /*<<< orphan*/  PllGfxclkSpreadFreq; int /*<<< orphan*/  PllGfxclkSpreadPercent; int /*<<< orphan*/  PllGfxclkSpreadEnabled; int /*<<< orphan*/  LedPin2; int /*<<< orphan*/  LedPin1; int /*<<< orphan*/  LedPin0; int /*<<< orphan*/  Padding2; int /*<<< orphan*/  Padding1; int /*<<< orphan*/  VR1HotPolarity; int /*<<< orphan*/  VR1HotGpio; int /*<<< orphan*/  VR0HotPolarity; int /*<<< orphan*/  VR0HotGpio; int /*<<< orphan*/  AcDcPolarity; int /*<<< orphan*/  AcDcGpio; int /*<<< orphan*/  Padding_TelemetryMem1; int /*<<< orphan*/  Mem1Offset; int /*<<< orphan*/  Mem1MaxCurrent; int /*<<< orphan*/  Padding_TelemetryMem0; int /*<<< orphan*/  Mem0Offset; int /*<<< orphan*/  Mem0MaxCurrent; int /*<<< orphan*/  Padding_TelemetrySoc; int /*<<< orphan*/  SocOffset; int /*<<< orphan*/  SocMaxCurrent; int /*<<< orphan*/  Padding_TelemetryGfx; int /*<<< orphan*/  GfxOffset; int /*<<< orphan*/  GfxMaxCurrent; int /*<<< orphan*/  ExternalSensorPresent; int /*<<< orphan*/  SocUlvPhaseSheddingMask; int /*<<< orphan*/  GfxUlvPhaseSheddingMask; int /*<<< orphan*/  VddMem1VrMapping; int /*<<< orphan*/  VddMem0VrMapping; int /*<<< orphan*/  VddSocVrMapping; int /*<<< orphan*/  VddGfxVrMapping; int /*<<< orphan*/  MaxVoltageStepSoc; int /*<<< orphan*/  MaxVoltageStepGfx; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2cspeed; int /*<<< orphan*/  i2cprotocol; int /*<<< orphan*/  thermalthrottler; int /*<<< orphan*/  controllerport; int /*<<< orphan*/  slaveaddress; int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  I2cSpeed; int /*<<< orphan*/  I2cProtocol; int /*<<< orphan*/  ThermalThrottler; int /*<<< orphan*/  ControllerPort; int /*<<< orphan*/  SlaveAddress; int /*<<< orphan*/  Enabled; } ;
typedef  TYPE_3__ PPTable_t ;

/* Variables and functions */
 int I2C_CONTROLLER_NAME_COUNT ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_dpm_info ; 
 int smu_get_atom_data_table (struct smu_context*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int vega20_append_powerplay_table(struct smu_context *smu)
{
	struct smu_table_context *table_context = &smu->smu_table;
	PPTable_t *smc_pptable = table_context->driver_pptable;
	struct atom_smc_dpm_info_v4_4 *smc_dpm_table;
	int index, i, ret;

	index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
					   smc_dpm_info);

	ret = smu_get_atom_data_table(smu, index, NULL, NULL, NULL,
				      (uint8_t **)&smc_dpm_table);
	if (ret)
		return ret;

	smc_pptable->MaxVoltageStepGfx = smc_dpm_table->maxvoltagestepgfx;
	smc_pptable->MaxVoltageStepSoc = smc_dpm_table->maxvoltagestepsoc;

	smc_pptable->VddGfxVrMapping = smc_dpm_table->vddgfxvrmapping;
	smc_pptable->VddSocVrMapping = smc_dpm_table->vddsocvrmapping;
	smc_pptable->VddMem0VrMapping = smc_dpm_table->vddmem0vrmapping;
	smc_pptable->VddMem1VrMapping = smc_dpm_table->vddmem1vrmapping;

	smc_pptable->GfxUlvPhaseSheddingMask = smc_dpm_table->gfxulvphasesheddingmask;
	smc_pptable->SocUlvPhaseSheddingMask = smc_dpm_table->soculvphasesheddingmask;
	smc_pptable->ExternalSensorPresent = smc_dpm_table->externalsensorpresent;

	smc_pptable->GfxMaxCurrent = smc_dpm_table->gfxmaxcurrent;
	smc_pptable->GfxOffset = smc_dpm_table->gfxoffset;
	smc_pptable->Padding_TelemetryGfx = smc_dpm_table->padding_telemetrygfx;

	smc_pptable->SocMaxCurrent = smc_dpm_table->socmaxcurrent;
	smc_pptable->SocOffset = smc_dpm_table->socoffset;
	smc_pptable->Padding_TelemetrySoc = smc_dpm_table->padding_telemetrysoc;

	smc_pptable->Mem0MaxCurrent = smc_dpm_table->mem0maxcurrent;
	smc_pptable->Mem0Offset = smc_dpm_table->mem0offset;
	smc_pptable->Padding_TelemetryMem0 = smc_dpm_table->padding_telemetrymem0;

	smc_pptable->Mem1MaxCurrent = smc_dpm_table->mem1maxcurrent;
	smc_pptable->Mem1Offset = smc_dpm_table->mem1offset;
	smc_pptable->Padding_TelemetryMem1 = smc_dpm_table->padding_telemetrymem1;

	smc_pptable->AcDcGpio = smc_dpm_table->acdcgpio;
	smc_pptable->AcDcPolarity = smc_dpm_table->acdcpolarity;
	smc_pptable->VR0HotGpio = smc_dpm_table->vr0hotgpio;
	smc_pptable->VR0HotPolarity = smc_dpm_table->vr0hotpolarity;

	smc_pptable->VR1HotGpio = smc_dpm_table->vr1hotgpio;
	smc_pptable->VR1HotPolarity = smc_dpm_table->vr1hotpolarity;
	smc_pptable->Padding1 = smc_dpm_table->padding1;
	smc_pptable->Padding2 = smc_dpm_table->padding2;

	smc_pptable->LedPin0 = smc_dpm_table->ledpin0;
	smc_pptable->LedPin1 = smc_dpm_table->ledpin1;
	smc_pptable->LedPin2 = smc_dpm_table->ledpin2;

	smc_pptable->PllGfxclkSpreadEnabled = smc_dpm_table->pllgfxclkspreadenabled;
	smc_pptable->PllGfxclkSpreadPercent = smc_dpm_table->pllgfxclkspreadpercent;
	smc_pptable->PllGfxclkSpreadFreq = smc_dpm_table->pllgfxclkspreadfreq;

	smc_pptable->UclkSpreadEnabled = 0;
	smc_pptable->UclkSpreadPercent = smc_dpm_table->uclkspreadpercent;
	smc_pptable->UclkSpreadFreq = smc_dpm_table->uclkspreadfreq;

	smc_pptable->FclkSpreadEnabled = smc_dpm_table->fclkspreadenabled;
	smc_pptable->FclkSpreadPercent = smc_dpm_table->fclkspreadpercent;
	smc_pptable->FclkSpreadFreq = smc_dpm_table->fclkspreadfreq;

	smc_pptable->FllGfxclkSpreadEnabled = smc_dpm_table->fllgfxclkspreadenabled;
	smc_pptable->FllGfxclkSpreadPercent = smc_dpm_table->fllgfxclkspreadpercent;
	smc_pptable->FllGfxclkSpreadFreq = smc_dpm_table->fllgfxclkspreadfreq;

	for (i = 0; i < I2C_CONTROLLER_NAME_COUNT; i++) {
		smc_pptable->I2cControllers[i].Enabled =
			smc_dpm_table->i2ccontrollers[i].enabled;
		smc_pptable->I2cControllers[i].SlaveAddress =
			smc_dpm_table->i2ccontrollers[i].slaveaddress;
		smc_pptable->I2cControllers[i].ControllerPort =
			smc_dpm_table->i2ccontrollers[i].controllerport;
		smc_pptable->I2cControllers[i].ThermalThrottler =
			smc_dpm_table->i2ccontrollers[i].thermalthrottler;
		smc_pptable->I2cControllers[i].I2cProtocol =
			smc_dpm_table->i2ccontrollers[i].i2cprotocol;
		smc_pptable->I2cControllers[i].I2cSpeed =
			smc_dpm_table->i2ccontrollers[i].i2cspeed;
	}

	return 0;
}
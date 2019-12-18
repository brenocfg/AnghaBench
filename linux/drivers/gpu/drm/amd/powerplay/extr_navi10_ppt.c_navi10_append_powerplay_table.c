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
typedef  int /*<<< orphan*/  uint8_t ;
struct smu_table_context {TYPE_2__* driver_pptable; } ;
struct smu_context {struct smu_table_context smu_table; struct amdgpu_device* adev; } ;
struct atom_smc_dpm_info_v4_5 {int /*<<< orphan*/  MvddRatio; int /*<<< orphan*/  BoardPadding; int /*<<< orphan*/  TotalBoardPower; int /*<<< orphan*/  SocclkSpreadFreq; int /*<<< orphan*/  SocclkSpreadPercent; int /*<<< orphan*/  SoclkSpreadEnabled; int /*<<< orphan*/  UclkSpreadFreq; int /*<<< orphan*/  UclkSpreadPercent; int /*<<< orphan*/  UclkSpreadEnabled; int /*<<< orphan*/  DfllGfxclkSpreadFreq; int /*<<< orphan*/  DfllGfxclkSpreadPercent; int /*<<< orphan*/  DfllGfxclkSpreadEnabled; int /*<<< orphan*/  PllGfxclkSpreadFreq; int /*<<< orphan*/  PllGfxclkSpreadPercent; int /*<<< orphan*/  PllGfxclkSpreadEnabled; int /*<<< orphan*/  padding8_4; int /*<<< orphan*/  LedPin2; int /*<<< orphan*/  LedPin1; int /*<<< orphan*/  LedPin0; int /*<<< orphan*/  GthrPolarity; int /*<<< orphan*/  GthrGpio; int /*<<< orphan*/  VR1HotPolarity; int /*<<< orphan*/  VR1HotGpio; int /*<<< orphan*/  VR0HotPolarity; int /*<<< orphan*/  VR0HotGpio; int /*<<< orphan*/  AcDcPolarity; int /*<<< orphan*/  AcDcGpio; int /*<<< orphan*/  Padding_TelemetryMem1; int /*<<< orphan*/  Mem1Offset; int /*<<< orphan*/  Mem1MaxCurrent; int /*<<< orphan*/  Padding_TelemetryMem0; int /*<<< orphan*/  Mem0Offset; int /*<<< orphan*/  Mem0MaxCurrent; int /*<<< orphan*/  Padding_TelemetrySoc; int /*<<< orphan*/  SocOffset; int /*<<< orphan*/  SocMaxCurrent; int /*<<< orphan*/  Padding_TelemetryGfx; int /*<<< orphan*/  GfxOffset; int /*<<< orphan*/  GfxMaxCurrent; int /*<<< orphan*/  Padding8_V; int /*<<< orphan*/  ExternalSensorPresent; int /*<<< orphan*/  SocUlvPhaseSheddingMask; int /*<<< orphan*/  GfxUlvPhaseSheddingMask; int /*<<< orphan*/  VddMem1VrMapping; int /*<<< orphan*/  VddMem0VrMapping; int /*<<< orphan*/  VddSocVrMapping; int /*<<< orphan*/  VddGfxVrMapping; int /*<<< orphan*/  MaxVoltageStepSoc; int /*<<< orphan*/  MaxVoltageStepGfx; int /*<<< orphan*/  I2cControllers; } ;
struct TYPE_3__ {int pp_feature; } ;
struct amdgpu_device {TYPE_1__ pm; } ;
struct TYPE_4__ {int /*<<< orphan*/  DebugOverrides; int /*<<< orphan*/  MvddRatio; int /*<<< orphan*/  BoardPadding; int /*<<< orphan*/  TotalBoardPower; int /*<<< orphan*/  SocclkSpreadFreq; int /*<<< orphan*/  SocclkSpreadPercent; int /*<<< orphan*/  SoclkSpreadEnabled; int /*<<< orphan*/  UclkSpreadFreq; int /*<<< orphan*/  UclkSpreadPercent; int /*<<< orphan*/  UclkSpreadEnabled; int /*<<< orphan*/  DfllGfxclkSpreadFreq; int /*<<< orphan*/  DfllGfxclkSpreadPercent; int /*<<< orphan*/  DfllGfxclkSpreadEnabled; int /*<<< orphan*/  PllGfxclkSpreadFreq; int /*<<< orphan*/  PllGfxclkSpreadPercent; int /*<<< orphan*/  PllGfxclkSpreadEnabled; int /*<<< orphan*/  padding8_4; int /*<<< orphan*/  LedPin2; int /*<<< orphan*/  LedPin1; int /*<<< orphan*/  LedPin0; int /*<<< orphan*/  GthrPolarity; int /*<<< orphan*/  GthrGpio; int /*<<< orphan*/  VR1HotPolarity; int /*<<< orphan*/  VR1HotGpio; int /*<<< orphan*/  VR0HotPolarity; int /*<<< orphan*/  VR0HotGpio; int /*<<< orphan*/  AcDcPolarity; int /*<<< orphan*/  AcDcGpio; int /*<<< orphan*/  Padding_TelemetryMem1; int /*<<< orphan*/  Mem1Offset; int /*<<< orphan*/  Mem1MaxCurrent; int /*<<< orphan*/  Padding_TelemetryMem0; int /*<<< orphan*/  Mem0Offset; int /*<<< orphan*/  Mem0MaxCurrent; int /*<<< orphan*/  Padding_TelemetrySoc; int /*<<< orphan*/  SocOffset; int /*<<< orphan*/  SocMaxCurrent; int /*<<< orphan*/  Padding_TelemetryGfx; int /*<<< orphan*/  GfxOffset; int /*<<< orphan*/  GfxMaxCurrent; int /*<<< orphan*/  Padding8_V; int /*<<< orphan*/  ExternalSensorPresent; int /*<<< orphan*/  SocUlvPhaseSheddingMask; int /*<<< orphan*/  GfxUlvPhaseSheddingMask; int /*<<< orphan*/  VddMem1VrMapping; int /*<<< orphan*/  VddMem0VrMapping; int /*<<< orphan*/  VddSocVrMapping; int /*<<< orphan*/  VddGfxVrMapping; int /*<<< orphan*/  MaxVoltageStepSoc; int /*<<< orphan*/  MaxVoltageStepGfx; int /*<<< orphan*/  I2cControllers; } ;
typedef  TYPE_2__ PPTable_t ;
typedef  int /*<<< orphan*/  I2cControllerConfig_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_OVERRIDE_DISABLE_DFLL_PLL_SHUTDOWN ; 
 int NUM_I2C_CONTROLLERS ; 
 int PP_GFXOFF_MASK ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smc_dpm_info ; 
 int smu_get_atom_data_table (struct smu_context*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int navi10_append_powerplay_table(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	struct smu_table_context *table_context = &smu->smu_table;
	PPTable_t *smc_pptable = table_context->driver_pptable;
	struct atom_smc_dpm_info_v4_5 *smc_dpm_table;
	int index, ret;

	index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
					   smc_dpm_info);

	ret = smu_get_atom_data_table(smu, index, NULL, NULL, NULL,
				      (uint8_t **)&smc_dpm_table);
	if (ret)
		return ret;

	memcpy(smc_pptable->I2cControllers, smc_dpm_table->I2cControllers,
	       sizeof(I2cControllerConfig_t) * NUM_I2C_CONTROLLERS);

	/* SVI2 Board Parameters */
	smc_pptable->MaxVoltageStepGfx = smc_dpm_table->MaxVoltageStepGfx;
	smc_pptable->MaxVoltageStepSoc = smc_dpm_table->MaxVoltageStepSoc;
	smc_pptable->VddGfxVrMapping = smc_dpm_table->VddGfxVrMapping;
	smc_pptable->VddSocVrMapping = smc_dpm_table->VddSocVrMapping;
	smc_pptable->VddMem0VrMapping = smc_dpm_table->VddMem0VrMapping;
	smc_pptable->VddMem1VrMapping = smc_dpm_table->VddMem1VrMapping;
	smc_pptable->GfxUlvPhaseSheddingMask = smc_dpm_table->GfxUlvPhaseSheddingMask;
	smc_pptable->SocUlvPhaseSheddingMask = smc_dpm_table->SocUlvPhaseSheddingMask;
	smc_pptable->ExternalSensorPresent = smc_dpm_table->ExternalSensorPresent;
	smc_pptable->Padding8_V = smc_dpm_table->Padding8_V;

	/* Telemetry Settings */
	smc_pptable->GfxMaxCurrent = smc_dpm_table->GfxMaxCurrent;
	smc_pptable->GfxOffset = smc_dpm_table->GfxOffset;
	smc_pptable->Padding_TelemetryGfx = smc_dpm_table->Padding_TelemetryGfx;
	smc_pptable->SocMaxCurrent = smc_dpm_table->SocMaxCurrent;
	smc_pptable->SocOffset = smc_dpm_table->SocOffset;
	smc_pptable->Padding_TelemetrySoc = smc_dpm_table->Padding_TelemetrySoc;
	smc_pptable->Mem0MaxCurrent = smc_dpm_table->Mem0MaxCurrent;
	smc_pptable->Mem0Offset = smc_dpm_table->Mem0Offset;
	smc_pptable->Padding_TelemetryMem0 = smc_dpm_table->Padding_TelemetryMem0;
	smc_pptable->Mem1MaxCurrent = smc_dpm_table->Mem1MaxCurrent;
	smc_pptable->Mem1Offset = smc_dpm_table->Mem1Offset;
	smc_pptable->Padding_TelemetryMem1 = smc_dpm_table->Padding_TelemetryMem1;

	/* GPIO Settings */
	smc_pptable->AcDcGpio = smc_dpm_table->AcDcGpio;
	smc_pptable->AcDcPolarity = smc_dpm_table->AcDcPolarity;
	smc_pptable->VR0HotGpio = smc_dpm_table->VR0HotGpio;
	smc_pptable->VR0HotPolarity = smc_dpm_table->VR0HotPolarity;
	smc_pptable->VR1HotGpio = smc_dpm_table->VR1HotGpio;
	smc_pptable->VR1HotPolarity = smc_dpm_table->VR1HotPolarity;
	smc_pptable->GthrGpio = smc_dpm_table->GthrGpio;
	smc_pptable->GthrPolarity = smc_dpm_table->GthrPolarity;

	/* LED Display Settings */
	smc_pptable->LedPin0 = smc_dpm_table->LedPin0;
	smc_pptable->LedPin1 = smc_dpm_table->LedPin1;
	smc_pptable->LedPin2 = smc_dpm_table->LedPin2;
	smc_pptable->padding8_4 = smc_dpm_table->padding8_4;

	/* GFXCLK PLL Spread Spectrum */
	smc_pptable->PllGfxclkSpreadEnabled = smc_dpm_table->PllGfxclkSpreadEnabled;
	smc_pptable->PllGfxclkSpreadPercent = smc_dpm_table->PllGfxclkSpreadPercent;
	smc_pptable->PllGfxclkSpreadFreq = smc_dpm_table->PllGfxclkSpreadFreq;

	/* GFXCLK DFLL Spread Spectrum */
	smc_pptable->DfllGfxclkSpreadEnabled = smc_dpm_table->DfllGfxclkSpreadEnabled;
	smc_pptable->DfllGfxclkSpreadPercent = smc_dpm_table->DfllGfxclkSpreadPercent;
	smc_pptable->DfllGfxclkSpreadFreq = smc_dpm_table->DfllGfxclkSpreadFreq;

	/* UCLK Spread Spectrum */
	smc_pptable->UclkSpreadEnabled = smc_dpm_table->UclkSpreadEnabled;
	smc_pptable->UclkSpreadPercent = smc_dpm_table->UclkSpreadPercent;
	smc_pptable->UclkSpreadFreq = smc_dpm_table->UclkSpreadFreq;

	/* SOCCLK Spread Spectrum */
	smc_pptable->SoclkSpreadEnabled = smc_dpm_table->SoclkSpreadEnabled;
	smc_pptable->SocclkSpreadPercent = smc_dpm_table->SocclkSpreadPercent;
	smc_pptable->SocclkSpreadFreq = smc_dpm_table->SocclkSpreadFreq;

	/* Total board power */
	smc_pptable->TotalBoardPower = smc_dpm_table->TotalBoardPower;
	smc_pptable->BoardPadding = smc_dpm_table->BoardPadding;

	/* Mvdd Svi2 Div Ratio Setting */
	smc_pptable->MvddRatio = smc_dpm_table->MvddRatio;

	if (adev->pm.pp_feature & PP_GFXOFF_MASK) {
		/* TODO: remove it once SMU fw fix it */
		smc_pptable->DebugOverrides |= DPM_OVERRIDE_DISABLE_DFLL_PLL_SHUTDOWN;
	}

	return 0;
}
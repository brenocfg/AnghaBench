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
struct TYPE_6__ {int LoadLineResistance; int /*<<< orphan*/  Plx_I2C_LineSDA; int /*<<< orphan*/  Plx_I2C_LineSCL; int /*<<< orphan*/  Vr_I2C_LineSDA; int /*<<< orphan*/  Vr_I2C_LineSCL; int /*<<< orphan*/  Liquid_I2C_LineSDA; int /*<<< orphan*/  Liquid_I2C_LineSCL; int /*<<< orphan*/  Plx_I2C_address; int /*<<< orphan*/  Vr_I2C_address; int /*<<< orphan*/  Liquid2_I2C_address; int /*<<< orphan*/  Liquid1_I2C_address; scalar_t__ FitLimit; void* TplxLimit; void* Tliquid2Limit; void* Tliquid1Limit; void* Tvr_memLimit; void* Tvr_socLimit; void* ThbmLimit; void* ThotspotLimit; void* TedgeLimit; void* EdcLimit; void* TdcLimit; void* SocketPowerLimit; } ;
struct TYPE_4__ {TYPE_3__ pp_table; } ;
struct vega10_hwmgr {TYPE_1__ smc_state_table; } ;
struct TYPE_5__ {int LoadLineSlope; } ;
struct pp_hwmgr {TYPE_2__ platform_descriptor; scalar_t__ pptable; struct vega10_hwmgr* backend; } ;
struct phm_tdp_table {int /*<<< orphan*/  ucPlx_I2C_LineSDA; int /*<<< orphan*/  ucPlx_I2C_Line; int /*<<< orphan*/  ucVr_I2C_LineSDA; int /*<<< orphan*/  ucVr_I2C_Line; int /*<<< orphan*/  ucLiquid_I2C_LineSDA; int /*<<< orphan*/  ucLiquid_I2C_Line; int /*<<< orphan*/  ucPlx_I2C_address; int /*<<< orphan*/  ucVr_I2C_address; int /*<<< orphan*/  ucLiquid2_I2C_address; int /*<<< orphan*/  ucLiquid1_I2C_address; int /*<<< orphan*/  usTemperatureLimitPlx; int /*<<< orphan*/  usTemperatureLimitLiquid2; int /*<<< orphan*/  usTemperatureLimitLiquid1; int /*<<< orphan*/  usTemperatureLimitVrMvdd; int /*<<< orphan*/  usTemperatureLimitVrVddc; int /*<<< orphan*/  usTemperatureLimitHBM; int /*<<< orphan*/  usTemperatureLimitHotspot; int /*<<< orphan*/  usTemperatureLimitTedge; int /*<<< orphan*/  usEDCLimit; int /*<<< orphan*/  usTDC; int /*<<< orphan*/  usMaximumPowerDeliveryLimit; } ;
struct phm_ppt_v2_information {struct phm_tdp_table* tdp_table; } ;
typedef  TYPE_3__ PPTable_t ;

/* Variables and functions */
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

void vega10_initialize_power_tune_defaults(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);
	struct phm_tdp_table *tdp_table = table_info->tdp_table;
	PPTable_t *table = &(data->smc_state_table.pp_table);

	table->SocketPowerLimit = cpu_to_le16(
			tdp_table->usMaximumPowerDeliveryLimit);
	table->TdcLimit = cpu_to_le16(tdp_table->usTDC);
	table->EdcLimit = cpu_to_le16(tdp_table->usEDCLimit);
	table->TedgeLimit = cpu_to_le16(tdp_table->usTemperatureLimitTedge);
	table->ThotspotLimit = cpu_to_le16(tdp_table->usTemperatureLimitHotspot);
	table->ThbmLimit = cpu_to_le16(tdp_table->usTemperatureLimitHBM);
	table->Tvr_socLimit = cpu_to_le16(tdp_table->usTemperatureLimitVrVddc);
	table->Tvr_memLimit = cpu_to_le16(tdp_table->usTemperatureLimitVrMvdd);
	table->Tliquid1Limit = cpu_to_le16(tdp_table->usTemperatureLimitLiquid1);
	table->Tliquid2Limit = cpu_to_le16(tdp_table->usTemperatureLimitLiquid2);
	table->TplxLimit = cpu_to_le16(tdp_table->usTemperatureLimitPlx);
	table->LoadLineResistance =
			hwmgr->platform_descriptor.LoadLineSlope * 256;
	table->FitLimit = 0; /* Not used for Vega10 */

	table->Liquid1_I2C_address = tdp_table->ucLiquid1_I2C_address;
	table->Liquid2_I2C_address = tdp_table->ucLiquid2_I2C_address;
	table->Vr_I2C_address = tdp_table->ucVr_I2C_address;
	table->Plx_I2C_address = tdp_table->ucPlx_I2C_address;

	table->Liquid_I2C_LineSCL = tdp_table->ucLiquid_I2C_Line;
	table->Liquid_I2C_LineSDA = tdp_table->ucLiquid_I2C_LineSDA;

	table->Vr_I2C_LineSCL = tdp_table->ucVr_I2C_Line;
	table->Vr_I2C_LineSDA = tdp_table->ucVr_I2C_LineSDA;

	table->Plx_I2C_LineSCL = tdp_table->ucPlx_I2C_Line;
	table->Plx_I2C_LineSDA = tdp_table->ucPlx_I2C_LineSDA;
}
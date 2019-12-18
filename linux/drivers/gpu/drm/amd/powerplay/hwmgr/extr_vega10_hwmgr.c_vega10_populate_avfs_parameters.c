#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  size_t uint32_t ;
typedef  void* uint16_t ;
struct TYPE_22__ {int m1_shift; int m2_shift; scalar_t__ b_shift; int /*<<< orphan*/  b; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; } ;
struct TYPE_21__ {int a0_shift; int a1_shift; int a2_shift; int /*<<< orphan*/  a2; int /*<<< orphan*/  a1; int /*<<< orphan*/  a0; } ;
struct TYPE_18__ {int m1_shift; int m2_shift; scalar_t__ b_shift; void* b; void* m2; void* m1; } ;
struct TYPE_17__ {int m1_shift; int m2_shift; scalar_t__ b_shift; void* b; void* m2; void* m1; } ;
struct TYPE_16__ {int a0_shift; int a1_shift; int a2_shift; void* a2; void* a1; void* a0; } ;
struct TYPE_15__ {int a0_shift; int a1_shift; int a2_shift; void* a2; void* a1; void* a0; } ;
struct TYPE_13__ {TYPE_9__ AcgAvfsGb; TYPE_8__ AcgBtcGbVdroopTable; TYPE_7__* DisplayClock2Gfxclk; scalar_t__* StaticVoltageOffsetVid; TYPE_5__ AvfsGbCksOff; int /*<<< orphan*/  OverrideAvfsGbCksOn; TYPE_4__ AvfsGbCksOn; TYPE_3__ BtcGbVdroopTableCksOn; int /*<<< orphan*/  OverrideBtcGbCksOn; TYPE_2__ BtcGbVdroopTableCksOff; void* PSM_Age_CompFactor; void* Platform_sigma; void* Platform_mean; void* DC_tol_sigma; void** AConstant; void* MaxVoltageVid; void* MinVoltageVid; } ;
struct TYPE_14__ {TYPE_11__ pp_table; } ;
struct vega10_hwmgr {scalar_t__ disp_clk_quad_eqn_a; scalar_t__ disp_clk_quad_eqn_b; scalar_t__ dcef_clk_quad_eqn_a; scalar_t__ dcef_clk_quad_eqn_b; scalar_t__ pixel_clk_quad_eqn_a; scalar_t__ pixel_clk_quad_eqn_b; scalar_t__ phy_clk_quad_eqn_a; scalar_t__ phy_clk_quad_eqn_b; TYPE_10__* smu_features; scalar_t__ phy_clk_quad_eqn_c; scalar_t__ pixel_clk_quad_eqn_c; scalar_t__ dcef_clk_quad_eqn_c; scalar_t__ disp_clk_quad_eqn_c; TYPE_1__ smc_state_table; } ;
struct pp_hwmgr {scalar_t__ pptable; struct vega10_hwmgr* backend; } ;
struct pp_atomfwctrl_avfs_parameters {int /*<<< orphan*/  ulAcgGbFuseTableB; int /*<<< orphan*/  ulAcgGbFuseTableM2; int /*<<< orphan*/  ulAcgGbFuseTableM1; int /*<<< orphan*/  ulAcgGbVdroopTableA2; int /*<<< orphan*/  ulAcgGbVdroopTableA1; int /*<<< orphan*/  ulAcgGbVdroopTableA0; scalar_t__ ulPhyclk2GfxclkB; scalar_t__ ulPhyclk2GfxclkM2; scalar_t__ ulPhyclk2GfxclkM1; scalar_t__ ulPixelclk2GfxclkB; scalar_t__ ulPixelclk2GfxclkM2; scalar_t__ ulPixelclk2GfxclkM1; scalar_t__ ulDcefclk2GfxclkB; scalar_t__ ulDcefclk2GfxclkM2; scalar_t__ ulDcefclk2GfxclkM1; scalar_t__ ulDispclk2GfxclkB; scalar_t__ ulDispclk2GfxclkM2; scalar_t__ ulDispclk2GfxclkM1; int /*<<< orphan*/  ulGbFuseTableCksoffB; int /*<<< orphan*/  ulGbFuseTableCksoffM2; int /*<<< orphan*/  ulGbFuseTableCksoffM1; int /*<<< orphan*/  ucEnableGbFuseTableCkson; int /*<<< orphan*/  ulGbFuseTableCksonB; int /*<<< orphan*/  ulGbFuseTableCksonM2; int /*<<< orphan*/  ulGbFuseTableCksonM1; int /*<<< orphan*/  ulGbVdroopTableCksonA2; int /*<<< orphan*/  ulGbVdroopTableCksonA1; int /*<<< orphan*/  ulGbVdroopTableCksonA0; int /*<<< orphan*/  ucEnableGbVdroopTableCkson; int /*<<< orphan*/  ulGbVdroopTableCksoffA2; int /*<<< orphan*/  ulGbVdroopTableCksoffA1; int /*<<< orphan*/  ulGbVdroopTableCksoffA0; int /*<<< orphan*/  usPsmAgeComfactor; int /*<<< orphan*/  usMeanNsigmaDcTolSigma; int /*<<< orphan*/  usMeanNsigmaPlatformMean; int /*<<< orphan*/  ulMeanNsigmaAcontant2; int /*<<< orphan*/  ulMeanNsigmaAcontant1; int /*<<< orphan*/  ulMeanNsigmaAcontant0; scalar_t__ ulMaxVddc; scalar_t__ ulMinVddc; int /*<<< orphan*/  member_0; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_6__* entries; } ;
typedef  void* int32_t ;
struct TYPE_20__ {int m1_shift; int m2_shift; int b_shift; void* b; void* m2; void* m1; } ;
struct TYPE_19__ {scalar_t__ sclk_offset; } ;
struct TYPE_12__ {int supported; } ;
typedef  TYPE_11__ PPTable_t ;

/* Variables and functions */
 size_t DSPCLK_DCEFCLK ; 
 size_t DSPCLK_DISPCLK ; 
 size_t DSPCLK_PHYCLK ; 
 size_t DSPCLK_PIXCLK ; 
 size_t GNLD_AVFS ; 
 scalar_t__ PPREGKEY_VEGA10QUADRATICEQUATION_DFLT ; 
 scalar_t__ convert_to_vid (void*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int pp_atomfwctrl_get_avfs_information (struct pp_hwmgr*,struct pp_atomfwctrl_avfs_parameters*) ; 

__attribute__((used)) static int vega10_populate_avfs_parameters(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_sclk;
	struct pp_atomfwctrl_avfs_parameters avfs_params = {0};
	int result = 0;
	uint32_t i;

	pp_table->MinVoltageVid = (uint8_t)0xff;
	pp_table->MaxVoltageVid = (uint8_t)0;

	if (data->smu_features[GNLD_AVFS].supported) {
		result = pp_atomfwctrl_get_avfs_information(hwmgr, &avfs_params);
		if (!result) {
			pp_table->MinVoltageVid = (uint8_t)
					convert_to_vid((uint16_t)(avfs_params.ulMinVddc));
			pp_table->MaxVoltageVid = (uint8_t)
					convert_to_vid((uint16_t)(avfs_params.ulMaxVddc));

			pp_table->AConstant[0] = cpu_to_le32(avfs_params.ulMeanNsigmaAcontant0);
			pp_table->AConstant[1] = cpu_to_le32(avfs_params.ulMeanNsigmaAcontant1);
			pp_table->AConstant[2] = cpu_to_le32(avfs_params.ulMeanNsigmaAcontant2);
			pp_table->DC_tol_sigma = cpu_to_le16(avfs_params.usMeanNsigmaDcTolSigma);
			pp_table->Platform_mean = cpu_to_le16(avfs_params.usMeanNsigmaPlatformMean);
			pp_table->Platform_sigma = cpu_to_le16(avfs_params.usMeanNsigmaDcTolSigma);
			pp_table->PSM_Age_CompFactor = cpu_to_le16(avfs_params.usPsmAgeComfactor);

			pp_table->BtcGbVdroopTableCksOff.a0 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksoffA0);
			pp_table->BtcGbVdroopTableCksOff.a0_shift = 20;
			pp_table->BtcGbVdroopTableCksOff.a1 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksoffA1);
			pp_table->BtcGbVdroopTableCksOff.a1_shift = 20;
			pp_table->BtcGbVdroopTableCksOff.a2 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksoffA2);
			pp_table->BtcGbVdroopTableCksOff.a2_shift = 20;

			pp_table->OverrideBtcGbCksOn = avfs_params.ucEnableGbVdroopTableCkson;
			pp_table->BtcGbVdroopTableCksOn.a0 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksonA0);
			pp_table->BtcGbVdroopTableCksOn.a0_shift = 20;
			pp_table->BtcGbVdroopTableCksOn.a1 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksonA1);
			pp_table->BtcGbVdroopTableCksOn.a1_shift = 20;
			pp_table->BtcGbVdroopTableCksOn.a2 =
					cpu_to_le32(avfs_params.ulGbVdroopTableCksonA2);
			pp_table->BtcGbVdroopTableCksOn.a2_shift = 20;

			pp_table->AvfsGbCksOn.m1 =
					cpu_to_le32(avfs_params.ulGbFuseTableCksonM1);
			pp_table->AvfsGbCksOn.m2 =
					cpu_to_le32(avfs_params.ulGbFuseTableCksonM2);
			pp_table->AvfsGbCksOn.b =
					cpu_to_le32(avfs_params.ulGbFuseTableCksonB);
			pp_table->AvfsGbCksOn.m1_shift = 24;
			pp_table->AvfsGbCksOn.m2_shift = 12;
			pp_table->AvfsGbCksOn.b_shift = 0;

			pp_table->OverrideAvfsGbCksOn =
					avfs_params.ucEnableGbFuseTableCkson;
			pp_table->AvfsGbCksOff.m1 =
					cpu_to_le32(avfs_params.ulGbFuseTableCksoffM1);
			pp_table->AvfsGbCksOff.m2 =
					cpu_to_le32(avfs_params.ulGbFuseTableCksoffM2);
			pp_table->AvfsGbCksOff.b =
					cpu_to_le32(avfs_params.ulGbFuseTableCksoffB);
			pp_table->AvfsGbCksOff.m1_shift = 24;
			pp_table->AvfsGbCksOff.m2_shift = 12;
			pp_table->AvfsGbCksOff.b_shift = 0;

			for (i = 0; i < dep_table->count; i++)
				pp_table->StaticVoltageOffsetVid[i] =
						convert_to_vid((uint8_t)(dep_table->entries[i].sclk_offset));

			if ((PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->disp_clk_quad_eqn_a) &&
				(PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->disp_clk_quad_eqn_b)) {
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m1 =
						(int32_t)data->disp_clk_quad_eqn_a;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m2 =
						(int32_t)data->disp_clk_quad_eqn_b;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].b =
						(int32_t)data->disp_clk_quad_eqn_c;
			} else {
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m1 =
						(int32_t)avfs_params.ulDispclk2GfxclkM1;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m2 =
						(int32_t)avfs_params.ulDispclk2GfxclkM2;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].b =
						(int32_t)avfs_params.ulDispclk2GfxclkB;
			}

			pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m1_shift = 24;
			pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].m2_shift = 12;
			pp_table->DisplayClock2Gfxclk[DSPCLK_DISPCLK].b_shift = 12;

			if ((PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->dcef_clk_quad_eqn_a) &&
				(PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->dcef_clk_quad_eqn_b)) {
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m1 =
						(int32_t)data->dcef_clk_quad_eqn_a;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m2 =
						(int32_t)data->dcef_clk_quad_eqn_b;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].b =
						(int32_t)data->dcef_clk_quad_eqn_c;
			} else {
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m1 =
						(int32_t)avfs_params.ulDcefclk2GfxclkM1;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m2 =
						(int32_t)avfs_params.ulDcefclk2GfxclkM2;
				pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].b =
						(int32_t)avfs_params.ulDcefclk2GfxclkB;
			}

			pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m1_shift = 24;
			pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].m2_shift = 12;
			pp_table->DisplayClock2Gfxclk[DSPCLK_DCEFCLK].b_shift = 12;

			if ((PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->pixel_clk_quad_eqn_a) &&
				(PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->pixel_clk_quad_eqn_b)) {
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m1 =
						(int32_t)data->pixel_clk_quad_eqn_a;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m2 =
						(int32_t)data->pixel_clk_quad_eqn_b;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].b =
						(int32_t)data->pixel_clk_quad_eqn_c;
			} else {
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m1 =
						(int32_t)avfs_params.ulPixelclk2GfxclkM1;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m2 =
						(int32_t)avfs_params.ulPixelclk2GfxclkM2;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].b =
						(int32_t)avfs_params.ulPixelclk2GfxclkB;
			}

			pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m1_shift = 24;
			pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].m2_shift = 12;
			pp_table->DisplayClock2Gfxclk[DSPCLK_PIXCLK].b_shift = 12;
			if ((PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->phy_clk_quad_eqn_a) &&
				(PPREGKEY_VEGA10QUADRATICEQUATION_DFLT !=
					data->phy_clk_quad_eqn_b)) {
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m1 =
						(int32_t)data->phy_clk_quad_eqn_a;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m2 =
						(int32_t)data->phy_clk_quad_eqn_b;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].b =
						(int32_t)data->phy_clk_quad_eqn_c;
			} else {
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m1 =
						(int32_t)avfs_params.ulPhyclk2GfxclkM1;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m2 =
						(int32_t)avfs_params.ulPhyclk2GfxclkM2;
				pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].b =
						(int32_t)avfs_params.ulPhyclk2GfxclkB;
			}

			pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m1_shift = 24;
			pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].m2_shift = 12;
			pp_table->DisplayClock2Gfxclk[DSPCLK_PHYCLK].b_shift = 12;

			pp_table->AcgBtcGbVdroopTable.a0       = avfs_params.ulAcgGbVdroopTableA0;
			pp_table->AcgBtcGbVdroopTable.a0_shift = 20;
			pp_table->AcgBtcGbVdroopTable.a1       = avfs_params.ulAcgGbVdroopTableA1;
			pp_table->AcgBtcGbVdroopTable.a1_shift = 20;
			pp_table->AcgBtcGbVdroopTable.a2       = avfs_params.ulAcgGbVdroopTableA2;
			pp_table->AcgBtcGbVdroopTable.a2_shift = 20;

			pp_table->AcgAvfsGb.m1                   = avfs_params.ulAcgGbFuseTableM1;
			pp_table->AcgAvfsGb.m2                   = avfs_params.ulAcgGbFuseTableM2;
			pp_table->AcgAvfsGb.b                    = avfs_params.ulAcgGbFuseTableB;
			pp_table->AcgAvfsGb.m1_shift             = 24;
			pp_table->AcgAvfsGb.m2_shift             = 12;
			pp_table->AcgAvfsGb.b_shift              = 0;

		} else {
			data->smu_features[GNLD_AVFS].supported = false;
		}
	}

	return 0;
}
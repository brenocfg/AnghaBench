#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct TYPE_14__ {void* MaxVoltage; TYPE_4__* AVFSGB_FUSE_TABLE; TYPE_3__* BTCGB_VDROOP_TABLE; } ;
struct vegam_smumgr {TYPE_6__ smc_state_table; } ;
struct smu7_hwmgr {int avfs_vdroop_override_setting; int apply_avfs_cks_off_voltage; } ;
struct pp_hwmgr {int /*<<< orphan*/  avfs_supported; scalar_t__ pptable; scalar_t__ smu_backend; scalar_t__ backend; } ;
struct pp_atom_ctrl__avfs_parameters {int usAVFSGB_FUSE_TABLE_CKSON_m2; int usAVFSGB_FUSE_TABLE_CKSOFF_m2; int usMaxVoltage_0_25mv; int usAVFS_meanNsigma_DC_tol_sigma; int usAVFS_meanNsigma_Platform_mean; int usPSM_Age_ComFactor; int usAVFS_meanNsigma_Platform_sigma; int ucEnableGB_VDROOP_TABLE_CKSON; int ucEnableGB_VDROOP_TABLE_CKSOFF; int ucEnableGB_FUSE_TABLE_CKSON; int ucEnableGB_FUSE_TABLE_CKSOFF; int ucEnableApplyAVFS_CKS_OFF_Voltage; int /*<<< orphan*/  ulAVFS_meanNsigma_Acontant2; int /*<<< orphan*/  ulAVFS_meanNsigma_Acontant1; int /*<<< orphan*/  ulAVFS_meanNsigma_Acontant0; int /*<<< orphan*/  ulAVFSGB_FUSE_TABLE_CKSOFF_b; int /*<<< orphan*/  ulAVFSGB_FUSE_TABLE_CKSOFF_m1; int /*<<< orphan*/  ulAVFSGB_FUSE_TABLE_CKSON_b; int /*<<< orphan*/  ulAVFSGB_FUSE_TABLE_CKSON_m1; int /*<<< orphan*/  ulGB_VDROOP_TABLE_CKSOFF_a2; int /*<<< orphan*/  ulGB_VDROOP_TABLE_CKSOFF_a1; int /*<<< orphan*/  ulGB_VDROOP_TABLE_CKSOFF_a0; int /*<<< orphan*/  ulGB_VDROOP_TABLE_CKSON_a2; int /*<<< orphan*/  ulGB_VDROOP_TABLE_CKSON_a1; int /*<<< orphan*/  ulGB_VDROOP_TABLE_CKSON_a0; int /*<<< orphan*/  member_0; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_5__* entries; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {void** Sclk_Offset; TYPE_2__ member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {scalar_t__* Static_Voltage_Offset; void* Platform_sigma; void* PSM_Age_CompFactor; void* Platform_mean; void* DC_tol_sigma; void** Aconstant; TYPE_1__ member_0; } ;
struct TYPE_13__ {int cks_voffset; scalar_t__ sclk_offset; } ;
struct TYPE_12__ {int m1_shift; int m2_shift; void* b; void* m2; void* m1; } ;
struct TYPE_11__ {void* a2; void* a1; void* a0; } ;
typedef  TYPE_6__ SMU75_Discrete_DpmTable ;
typedef  TYPE_7__ AVFS_meanNsigma_t ;
typedef  TYPE_8__ AVFS_Sclk_Offset_t ;

/* Variables and functions */
 int AVFSGB0_Vdroop_Enable_SHIFT ; 
 int AVFSGB1_Vdroop_Enable_SHIFT ; 
 int /*<<< orphan*/  AvfsMeanNSigma ; 
 int /*<<< orphan*/  AvfsSclkOffsetTable ; 
 int BTCGB0_Vdroop_Enable_SHIFT ; 
 int BTCGB1_Vdroop_Enable_SHIFT ; 
 void* PP_HOST_TO_SMC_UL (int /*<<< orphan*/ ) ; 
 void* PP_HOST_TO_SMC_US (int) ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 int /*<<< orphan*/  SMU75_Firmware_Header ; 
 scalar_t__ SMU7_FIRMWARE_HEADER_LOCATION ; 
 int atomctrl_get_avfs_information (struct pp_hwmgr*,struct pp_atom_ctrl__avfs_parameters*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu7_copy_bytes_to_smc (struct pp_hwmgr*,size_t,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int smu7_read_smc_sram_dword (struct pp_hwmgr*,scalar_t__,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vegam_populate_avfs_parameters(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct vegam_smumgr *smu_data = (struct vegam_smumgr *)(hwmgr->smu_backend);

	SMU75_Discrete_DpmTable  *table = &(smu_data->smc_state_table);
	int result = 0;
	struct pp_atom_ctrl__avfs_parameters avfs_params = {0};
	AVFS_meanNsigma_t AVFS_meanNsigma = { {0} };
	AVFS_Sclk_Offset_t AVFS_SclkOffset = { {0} };
	uint32_t tmp, i;

	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)hwmgr->pptable;
	struct phm_ppt_v1_clock_voltage_dependency_table *sclk_table =
			table_info->vdd_dep_on_sclk;

	if (!hwmgr->avfs_supported)
		return 0;

	result = atomctrl_get_avfs_information(hwmgr, &avfs_params);

	if (0 == result) {
		table->BTCGB_VDROOP_TABLE[0].a0 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSON_a0);
		table->BTCGB_VDROOP_TABLE[0].a1 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSON_a1);
		table->BTCGB_VDROOP_TABLE[0].a2 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSON_a2);
		table->BTCGB_VDROOP_TABLE[1].a0 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a0);
		table->BTCGB_VDROOP_TABLE[1].a1 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a1);
		table->BTCGB_VDROOP_TABLE[1].a2 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a2);
		table->AVFSGB_FUSE_TABLE[0].m1 =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSON_m1);
		table->AVFSGB_FUSE_TABLE[0].m2 =
				PP_HOST_TO_SMC_US(avfs_params.usAVFSGB_FUSE_TABLE_CKSON_m2);
		table->AVFSGB_FUSE_TABLE[0].b =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSON_b);
		table->AVFSGB_FUSE_TABLE[0].m1_shift = 24;
		table->AVFSGB_FUSE_TABLE[0].m2_shift = 12;
		table->AVFSGB_FUSE_TABLE[1].m1 =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_m1);
		table->AVFSGB_FUSE_TABLE[1].m2 =
				PP_HOST_TO_SMC_US(avfs_params.usAVFSGB_FUSE_TABLE_CKSOFF_m2);
		table->AVFSGB_FUSE_TABLE[1].b =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_b);
		table->AVFSGB_FUSE_TABLE[1].m1_shift = 24;
		table->AVFSGB_FUSE_TABLE[1].m2_shift = 12;
		table->MaxVoltage = PP_HOST_TO_SMC_US(avfs_params.usMaxVoltage_0_25mv);
		AVFS_meanNsigma.Aconstant[0] =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFS_meanNsigma_Acontant0);
		AVFS_meanNsigma.Aconstant[1] =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFS_meanNsigma_Acontant1);
		AVFS_meanNsigma.Aconstant[2] =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFS_meanNsigma_Acontant2);
		AVFS_meanNsigma.DC_tol_sigma =
				PP_HOST_TO_SMC_US(avfs_params.usAVFS_meanNsigma_DC_tol_sigma);
		AVFS_meanNsigma.Platform_mean =
				PP_HOST_TO_SMC_US(avfs_params.usAVFS_meanNsigma_Platform_mean);
		AVFS_meanNsigma.PSM_Age_CompFactor =
				PP_HOST_TO_SMC_US(avfs_params.usPSM_Age_ComFactor);
		AVFS_meanNsigma.Platform_sigma =
				PP_HOST_TO_SMC_US(avfs_params.usAVFS_meanNsigma_Platform_sigma);

		for (i = 0; i < sclk_table->count; i++) {
			AVFS_meanNsigma.Static_Voltage_Offset[i] =
					(uint8_t)(sclk_table->entries[i].cks_voffset * 100 / 625);
			AVFS_SclkOffset.Sclk_Offset[i] =
					PP_HOST_TO_SMC_US((uint16_t)
							(sclk_table->entries[i].sclk_offset) / 100);
		}

		result = smu7_read_smc_sram_dword(hwmgr,
				SMU7_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU75_Firmware_Header, AvfsMeanNSigma),
				&tmp, SMC_RAM_END);
		smu7_copy_bytes_to_smc(hwmgr,
					tmp,
					(uint8_t *)&AVFS_meanNsigma,
					sizeof(AVFS_meanNsigma_t),
					SMC_RAM_END);

		result = smu7_read_smc_sram_dword(hwmgr,
				SMU7_FIRMWARE_HEADER_LOCATION +
				offsetof(SMU75_Firmware_Header, AvfsSclkOffsetTable),
				&tmp, SMC_RAM_END);
		smu7_copy_bytes_to_smc(hwmgr,
					tmp,
					(uint8_t *)&AVFS_SclkOffset,
					sizeof(AVFS_Sclk_Offset_t),
					SMC_RAM_END);

		data->avfs_vdroop_override_setting =
				(avfs_params.ucEnableGB_VDROOP_TABLE_CKSON << BTCGB0_Vdroop_Enable_SHIFT) |
				(avfs_params.ucEnableGB_VDROOP_TABLE_CKSOFF << BTCGB1_Vdroop_Enable_SHIFT) |
				(avfs_params.ucEnableGB_FUSE_TABLE_CKSON << AVFSGB0_Vdroop_Enable_SHIFT) |
				(avfs_params.ucEnableGB_FUSE_TABLE_CKSOFF << AVFSGB1_Vdroop_Enable_SHIFT);
		data->apply_avfs_cks_off_voltage =
				(avfs_params.ucEnableApplyAVFS_CKS_OFF_Voltage == 1) ? true : false;
	}
	return result;
}
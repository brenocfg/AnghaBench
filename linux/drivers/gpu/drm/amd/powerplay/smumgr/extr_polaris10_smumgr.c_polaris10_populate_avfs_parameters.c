#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct smu7_hwmgr {int avfs_vdroop_override_setting; int apply_avfs_cks_off_voltage; } ;
struct pp_hwmgr {scalar_t__ chip_id; int /*<<< orphan*/  is_kicker; int /*<<< orphan*/  avfs_supported; scalar_t__ pptable; struct amdgpu_device* adev; scalar_t__ smu_backend; scalar_t__ backend; } ;
struct pp_atom_ctrl__avfs_parameters {int ucEnableApplyAVFS_CKS_OFF_Voltage; int ulGB_VDROOP_TABLE_CKSOFF_a0; int ulGB_VDROOP_TABLE_CKSOFF_a1; int ulGB_VDROOP_TABLE_CKSOFF_a2; int ulAVFSGB_FUSE_TABLE_CKSOFF_m1; int usAVFSGB_FUSE_TABLE_CKSOFF_m2; int ulAVFSGB_FUSE_TABLE_CKSOFF_b; int ulGB_VDROOP_TABLE_CKSON_a0; int ulGB_VDROOP_TABLE_CKSON_a1; int ulGB_VDROOP_TABLE_CKSON_a2; int ulAVFSGB_FUSE_TABLE_CKSON_m1; int usAVFSGB_FUSE_TABLE_CKSON_m2; int ulAVFSGB_FUSE_TABLE_CKSON_b; int usMaxVoltage_0_25mv; int ulAVFS_meanNsigma_Acontant0; int ulAVFS_meanNsigma_Acontant1; int ulAVFS_meanNsigma_Acontant2; int usAVFS_meanNsigma_DC_tol_sigma; int usAVFS_meanNsigma_Platform_mean; int usPSM_Age_ComFactor; int usAVFS_meanNsigma_Platform_sigma; int ucEnableGB_VDROOP_TABLE_CKSON; int ucEnableGB_VDROOP_TABLE_CKSOFF; int ucEnableGB_FUSE_TABLE_CKSON; int ucEnableGB_FUSE_TABLE_CKSOFF; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {void* MaxVoltage; TYPE_2__* AVFSGB_VDROOP_TABLE; TYPE_1__* BTCGB_VDROOP_TABLE; } ;
struct polaris10_smumgr {TYPE_7__ smc_state_table; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {TYPE_3__* entries; } ;
struct amdgpu_device {TYPE_6__* pdev; } ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {void** Sclk_Offset; TYPE_5__ member_0; } ;
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {scalar_t__* Static_Voltage_Offset; void* Platform_sigma; void* PSM_Age_CompFactor; void* Platform_mean; void* DC_tol_sigma; void** Aconstant; TYPE_4__ member_0; } ;
struct TYPE_15__ {int device; int revision; } ;
struct TYPE_12__ {int cks_voffset; scalar_t__ sclk_offset; } ;
struct TYPE_11__ {int m1_shift; int m2_shift; void* b; void* m2; void* m1; } ;
struct TYPE_10__ {void* a2; void* a1; void* a0; } ;
typedef  TYPE_7__ SMU74_Discrete_DpmTable ;
typedef  TYPE_8__ AVFS_meanNsigma_t ;
typedef  TYPE_9__ AVFS_Sclk_Offset_t ;

/* Variables and functions */
 int AVFSGB0_Vdroop_Enable_SHIFT ; 
 int AVFSGB1_Vdroop_Enable_SHIFT ; 
 int /*<<< orphan*/  AvfsMeanNSigma ; 
 int /*<<< orphan*/  AvfsSclkOffsetTable ; 
 int BTCGB0_Vdroop_Enable_SHIFT ; 
 int BTCGB1_Vdroop_Enable_SHIFT ; 
 scalar_t__ CHIP_POLARIS12 ; 
 size_t NUM_VFT_COLUMNS ; 
 void* PP_HOST_TO_SMC_UL (int) ; 
 void* PP_HOST_TO_SMC_US (int) ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 int /*<<< orphan*/  SMU74_Firmware_Header ; 
 scalar_t__ SMU7_FIRMWARE_HEADER_LOCATION ; 
 int atomctrl_get_avfs_information (struct pp_hwmgr*,struct pp_atom_ctrl__avfs_parameters*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu7_copy_bytes_to_smc (struct pp_hwmgr*,size_t,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int smu7_read_smc_sram_dword (struct pp_hwmgr*,scalar_t__,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int polaris10_populate_avfs_parameters(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct polaris10_smumgr *smu_data = (struct polaris10_smumgr *)(hwmgr->smu_backend);
	struct amdgpu_device *adev = hwmgr->adev;

	SMU74_Discrete_DpmTable  *table = &(smu_data->smc_state_table);
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
		if (((adev->pdev->device == 0x67ef) &&
		     ((adev->pdev->revision == 0xe0) ||
		      (adev->pdev->revision == 0xe5))) ||
		    ((adev->pdev->device == 0x67ff) &&
		     ((adev->pdev->revision == 0xcf) ||
		      (adev->pdev->revision == 0xef) ||
		      (adev->pdev->revision == 0xff)))) {
			avfs_params.ucEnableApplyAVFS_CKS_OFF_Voltage = 1;
			if ((adev->pdev->device == 0x67ef && adev->pdev->revision == 0xe5) ||
			    (adev->pdev->device == 0x67ff && adev->pdev->revision == 0xef)) {
				if ((avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a0 == 0xEA522DD3) &&
				    (avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a1 == 0x5645A) &&
				    (avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a2 == 0x33F9E) &&
				    (avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_m1 == 0xFFFFC5CC) &&
				    (avfs_params.usAVFSGB_FUSE_TABLE_CKSOFF_m2 == 0x1B1A) &&
				    (avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_b == 0xFFFFFCED)) {
					avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a0   = 0xF718F1D4;
					avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a1   = 0x323FD;
					avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a2   = 0x1E455;
					avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_m1 = 0;
					avfs_params.usAVFSGB_FUSE_TABLE_CKSOFF_m2 = 0;
					avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_b  = 0x23;
				}
			}
		} else if (hwmgr->chip_id == CHIP_POLARIS12 && !hwmgr->is_kicker) {
			avfs_params.ucEnableApplyAVFS_CKS_OFF_Voltage = 1;
			avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a0   = 0xF6B024DD;
			avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a1   = 0x3005E;
			avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a2   = 0x18A5F;
			avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_m1 = 0x315;
			avfs_params.usAVFSGB_FUSE_TABLE_CKSOFF_m2 = 0xFED1;
			avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_b  = 0x3B;
		} else if (((adev->pdev->device == 0x67df) &&
			    ((adev->pdev->revision == 0xe0) ||
			     (adev->pdev->revision == 0xe3) ||
			     (adev->pdev->revision == 0xe4) ||
			     (adev->pdev->revision == 0xe5) ||
			     (adev->pdev->revision == 0xe7) ||
			     (adev->pdev->revision == 0xef))) ||
			   ((adev->pdev->device == 0x6fdf) &&
			    ((adev->pdev->revision == 0xef) ||
			     (adev->pdev->revision == 0xff)))) {
			avfs_params.ucEnableApplyAVFS_CKS_OFF_Voltage = 1;
			avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a0   = 0xF843B66B;
			avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a1   = 0x59CB5;
			avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a2   = 0xFFFF287F;
			avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_m1 = 0;
			avfs_params.usAVFSGB_FUSE_TABLE_CKSOFF_m2 = 0xFF23;
			avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_b  = 0x58;
		}
	}

	if (0 == result) {
		table->BTCGB_VDROOP_TABLE[0].a0  = PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSON_a0);
		table->BTCGB_VDROOP_TABLE[0].a1  = PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSON_a1);
		table->BTCGB_VDROOP_TABLE[0].a2  = PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSON_a2);
		table->BTCGB_VDROOP_TABLE[1].a0  = PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a0);
		table->BTCGB_VDROOP_TABLE[1].a1  = PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a1);
		table->BTCGB_VDROOP_TABLE[1].a2  = PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a2);
		table->AVFSGB_VDROOP_TABLE[0].m1 = PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSON_m1);
		table->AVFSGB_VDROOP_TABLE[0].m2 = PP_HOST_TO_SMC_US(avfs_params.usAVFSGB_FUSE_TABLE_CKSON_m2);
		table->AVFSGB_VDROOP_TABLE[0].b  = PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSON_b);
		table->AVFSGB_VDROOP_TABLE[0].m1_shift = 24;
		table->AVFSGB_VDROOP_TABLE[0].m2_shift  = 12;
		table->AVFSGB_VDROOP_TABLE[1].m1 = PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_m1);
		table->AVFSGB_VDROOP_TABLE[1].m2 = PP_HOST_TO_SMC_US(avfs_params.usAVFSGB_FUSE_TABLE_CKSOFF_m2);
		table->AVFSGB_VDROOP_TABLE[1].b  = PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_b);
		table->AVFSGB_VDROOP_TABLE[1].m1_shift = 24;
		table->AVFSGB_VDROOP_TABLE[1].m2_shift  = 12;
		table->MaxVoltage                = PP_HOST_TO_SMC_US(avfs_params.usMaxVoltage_0_25mv);
		AVFS_meanNsigma.Aconstant[0]      = PP_HOST_TO_SMC_UL(avfs_params.ulAVFS_meanNsigma_Acontant0);
		AVFS_meanNsigma.Aconstant[1]      = PP_HOST_TO_SMC_UL(avfs_params.ulAVFS_meanNsigma_Acontant1);
		AVFS_meanNsigma.Aconstant[2]      = PP_HOST_TO_SMC_UL(avfs_params.ulAVFS_meanNsigma_Acontant2);
		AVFS_meanNsigma.DC_tol_sigma      = PP_HOST_TO_SMC_US(avfs_params.usAVFS_meanNsigma_DC_tol_sigma);
		AVFS_meanNsigma.Platform_mean     = PP_HOST_TO_SMC_US(avfs_params.usAVFS_meanNsigma_Platform_mean);
		AVFS_meanNsigma.PSM_Age_CompFactor = PP_HOST_TO_SMC_US(avfs_params.usPSM_Age_ComFactor);
		AVFS_meanNsigma.Platform_sigma     = PP_HOST_TO_SMC_US(avfs_params.usAVFS_meanNsigma_Platform_sigma);

		for (i = 0; i < NUM_VFT_COLUMNS; i++) {
			AVFS_meanNsigma.Static_Voltage_Offset[i] = (uint8_t)(sclk_table->entries[i].cks_voffset * 100 / 625);
			AVFS_SclkOffset.Sclk_Offset[i] = PP_HOST_TO_SMC_US((uint16_t)(sclk_table->entries[i].sclk_offset) / 100);
		}

		result = smu7_read_smc_sram_dword(hwmgr,
				SMU7_FIRMWARE_HEADER_LOCATION + offsetof(SMU74_Firmware_Header, AvfsMeanNSigma),
				&tmp, SMC_RAM_END);

		smu7_copy_bytes_to_smc(hwmgr,
					tmp,
					(uint8_t *)&AVFS_meanNsigma,
					sizeof(AVFS_meanNsigma_t),
					SMC_RAM_END);

		result = smu7_read_smc_sram_dword(hwmgr,
				SMU7_FIRMWARE_HEADER_LOCATION + offsetof(SMU74_Firmware_Header, AvfsSclkOffsetTable),
				&tmp, SMC_RAM_END);
		smu7_copy_bytes_to_smc(hwmgr,
					tmp,
					(uint8_t *)&AVFS_SclkOffset,
					sizeof(AVFS_Sclk_Offset_t),
					SMC_RAM_END);

		data->avfs_vdroop_override_setting = (avfs_params.ucEnableGB_VDROOP_TABLE_CKSON << BTCGB0_Vdroop_Enable_SHIFT) |
						(avfs_params.ucEnableGB_VDROOP_TABLE_CKSOFF << BTCGB1_Vdroop_Enable_SHIFT) |
						(avfs_params.ucEnableGB_FUSE_TABLE_CKSON << AVFSGB0_Vdroop_Enable_SHIFT) |
						(avfs_params.ucEnableGB_FUSE_TABLE_CKSOFF << AVFSGB1_Vdroop_Enable_SHIFT);
		data->apply_avfs_cks_off_voltage = (avfs_params.ucEnableApplyAVFS_CKS_OFF_Voltage == 1) ? true : false;
	}
	return result;
}
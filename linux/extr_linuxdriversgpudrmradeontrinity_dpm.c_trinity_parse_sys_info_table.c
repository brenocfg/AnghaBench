#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ucHtcTmpLmt; int ucHtcHystLmt; int /*<<< orphan*/  ucDPMState3DclkFid; int /*<<< orphan*/  ucDPMState2DclkFid; int /*<<< orphan*/  ucDPMState1DclkFid; int /*<<< orphan*/  ucDPMState0DclkFid; int /*<<< orphan*/  ucDPMState3VclkFid; int /*<<< orphan*/  ucDPMState2VclkFid; int /*<<< orphan*/  ucDPMState1VclkFid; int /*<<< orphan*/  ucDPMState0VclkFid; int /*<<< orphan*/  sAvail_SCLK; int /*<<< orphan*/  ucUMAChannelNumber; int /*<<< orphan*/  usNBP3Voltage; int /*<<< orphan*/  usNBP2Voltage; int /*<<< orphan*/  usNBP1Voltage; int /*<<< orphan*/  usNBP0Voltage; int /*<<< orphan*/ * ulNbpStateNClkFreq; int /*<<< orphan*/ * ulNbpStateMemclkFreq; scalar_t__ ucNBDPMEnable; int /*<<< orphan*/  usBootUpNBVoltage; int /*<<< orphan*/  ulDentistVCOFreq; int /*<<< orphan*/  ulBootUpUMAClock; int /*<<< orphan*/  ulMinEngineClock; int /*<<< orphan*/  ulBootUpEngineClock; } ;
union igp_info {TYPE_3__ info_7; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int htc_tmp_lmt; int htc_hyst_lmt; TYPE_1__* uvd_clock_table_entries; int /*<<< orphan*/  vid_mapping_table; int /*<<< orphan*/  sclk_voltage_mapping_table; int /*<<< orphan*/  uma_channel_number; void** nbp_voltage_index; void** nbp_nclk; void** nbp_mclk; scalar_t__ nb_dpm_enable; void* bootup_nb_voltage_index; void* dentist_vco_freq; void* bootup_uma_clk; void* min_sclk; void* bootup_sclk; } ;
struct trinity_power_info {TYPE_2__ sys_info; scalar_t__ enable_nbps_policy; } ;
struct radeon_mode_info {TYPE_4__* atom_context; } ;
struct radeon_device {struct radeon_mode_info mode_info; } ;
struct TYPE_8__ {scalar_t__ bios; } ;
struct TYPE_5__ {int /*<<< orphan*/  dclk_did; void* dclk; int /*<<< orphan*/  vclk_did; void* vclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntegratedSystemInfo ; 
 int TRINITY_NUM_NBPSTATES ; 
 scalar_t__ atom_parse_data_header (TYPE_4__*,int,int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sumo_construct_sclk_voltage_mapping_table (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sumo_construct_vid_mapping_table (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* trinity_convert_did_to_freq (struct radeon_device*,int /*<<< orphan*/ ) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int trinity_parse_sys_info_table(struct radeon_device *rdev)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	union igp_info *igp_info;
	u8 frev, crev;
	u16 data_offset;
	int i;

	if (atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		igp_info = (union igp_info *)(mode_info->atom_context->bios +
					      data_offset);

		if (crev != 7) {
			DRM_ERROR("Unsupported IGP table: %d %d\n", frev, crev);
			return -EINVAL;
		}
		pi->sys_info.bootup_sclk = le32_to_cpu(igp_info->info_7.ulBootUpEngineClock);
		pi->sys_info.min_sclk = le32_to_cpu(igp_info->info_7.ulMinEngineClock);
		pi->sys_info.bootup_uma_clk = le32_to_cpu(igp_info->info_7.ulBootUpUMAClock);
		pi->sys_info.dentist_vco_freq = le32_to_cpu(igp_info->info_7.ulDentistVCOFreq);
		pi->sys_info.bootup_nb_voltage_index =
			le16_to_cpu(igp_info->info_7.usBootUpNBVoltage);
		if (igp_info->info_7.ucHtcTmpLmt == 0)
			pi->sys_info.htc_tmp_lmt = 203;
		else
			pi->sys_info.htc_tmp_lmt = igp_info->info_7.ucHtcTmpLmt;
		if (igp_info->info_7.ucHtcHystLmt == 0)
			pi->sys_info.htc_hyst_lmt = 5;
		else
			pi->sys_info.htc_hyst_lmt = igp_info->info_7.ucHtcHystLmt;
		if (pi->sys_info.htc_tmp_lmt <= pi->sys_info.htc_hyst_lmt) {
			DRM_ERROR("The htcTmpLmt should be larger than htcHystLmt.\n");
		}

		if (pi->enable_nbps_policy)
			pi->sys_info.nb_dpm_enable = igp_info->info_7.ucNBDPMEnable;
		else
			pi->sys_info.nb_dpm_enable = 0;

		for (i = 0; i < TRINITY_NUM_NBPSTATES; i++) {
			pi->sys_info.nbp_mclk[i] = le32_to_cpu(igp_info->info_7.ulNbpStateMemclkFreq[i]);
			pi->sys_info.nbp_nclk[i] = le32_to_cpu(igp_info->info_7.ulNbpStateNClkFreq[i]);
		}

		pi->sys_info.nbp_voltage_index[0] = le16_to_cpu(igp_info->info_7.usNBP0Voltage);
		pi->sys_info.nbp_voltage_index[1] = le16_to_cpu(igp_info->info_7.usNBP1Voltage);
		pi->sys_info.nbp_voltage_index[2] = le16_to_cpu(igp_info->info_7.usNBP2Voltage);
		pi->sys_info.nbp_voltage_index[3] = le16_to_cpu(igp_info->info_7.usNBP3Voltage);

		if (!pi->sys_info.nb_dpm_enable) {
			for (i = 1; i < TRINITY_NUM_NBPSTATES; i++) {
				pi->sys_info.nbp_mclk[i] = pi->sys_info.nbp_mclk[0];
				pi->sys_info.nbp_nclk[i] = pi->sys_info.nbp_nclk[0];
				pi->sys_info.nbp_voltage_index[i] = pi->sys_info.nbp_voltage_index[0];
			}
		}

		pi->sys_info.uma_channel_number = igp_info->info_7.ucUMAChannelNumber;

		sumo_construct_sclk_voltage_mapping_table(rdev,
							  &pi->sys_info.sclk_voltage_mapping_table,
							  igp_info->info_7.sAvail_SCLK);
		sumo_construct_vid_mapping_table(rdev, &pi->sys_info.vid_mapping_table,
						 igp_info->info_7.sAvail_SCLK);

		pi->sys_info.uvd_clock_table_entries[0].vclk_did =
			igp_info->info_7.ucDPMState0VclkFid;
		pi->sys_info.uvd_clock_table_entries[1].vclk_did =
			igp_info->info_7.ucDPMState1VclkFid;
		pi->sys_info.uvd_clock_table_entries[2].vclk_did =
			igp_info->info_7.ucDPMState2VclkFid;
		pi->sys_info.uvd_clock_table_entries[3].vclk_did =
			igp_info->info_7.ucDPMState3VclkFid;

		pi->sys_info.uvd_clock_table_entries[0].dclk_did =
			igp_info->info_7.ucDPMState0DclkFid;
		pi->sys_info.uvd_clock_table_entries[1].dclk_did =
			igp_info->info_7.ucDPMState1DclkFid;
		pi->sys_info.uvd_clock_table_entries[2].dclk_did =
			igp_info->info_7.ucDPMState2DclkFid;
		pi->sys_info.uvd_clock_table_entries[3].dclk_did =
			igp_info->info_7.ucDPMState3DclkFid;

		for (i = 0; i < 4; i++) {
			pi->sys_info.uvd_clock_table_entries[i].vclk =
				trinity_convert_did_to_freq(rdev,
							    pi->sys_info.uvd_clock_table_entries[i].vclk_did);
			pi->sys_info.uvd_clock_table_entries[i].dclk =
				trinity_convert_did_to_freq(rdev,
							    pi->sys_info.uvd_clock_table_entries[i].dclk_did);
		}



	}
	return 0;
}
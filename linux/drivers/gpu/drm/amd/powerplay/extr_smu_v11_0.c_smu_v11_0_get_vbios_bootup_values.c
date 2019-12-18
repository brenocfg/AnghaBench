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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int format_revision; int content_revision; int /*<<< orphan*/  pp_table_id; int /*<<< orphan*/  cooling_id; int /*<<< orphan*/  vdd_gfx; int /*<<< orphan*/  mvddc; int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; int /*<<< orphan*/  dcefclk; int /*<<< orphan*/  socclk; int /*<<< orphan*/  uclk; int /*<<< orphan*/  gfxclk; int /*<<< orphan*/  revision; } ;
struct TYPE_4__ {TYPE_1__ boot_values; } ;
struct smu_context {TYPE_2__ smu_table; } ;
struct atom_firmware_info_v3_3 {int /*<<< orphan*/  pplib_pptable_id; int /*<<< orphan*/  coolingsolution_id; int /*<<< orphan*/  bootup_vddgfx_mv; int /*<<< orphan*/  bootup_mvddc_mv; int /*<<< orphan*/  bootup_vddci_mv; int /*<<< orphan*/  bootup_vddc_mv; int /*<<< orphan*/  bootup_mclk_in10khz; int /*<<< orphan*/  bootup_sclk_in10khz; int /*<<< orphan*/  firmware_revision; } ;
struct atom_firmware_info_v3_1 {int /*<<< orphan*/  coolingsolution_id; int /*<<< orphan*/  bootup_vddgfx_mv; int /*<<< orphan*/  bootup_mvddc_mv; int /*<<< orphan*/  bootup_vddci_mv; int /*<<< orphan*/  bootup_vddc_mv; int /*<<< orphan*/  bootup_mclk_in10khz; int /*<<< orphan*/  bootup_sclk_in10khz; int /*<<< orphan*/  firmware_revision; } ;
struct atom_common_table_header {int format_revision; int content_revision; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int /*<<< orphan*/  firmwareinfo ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int smu_get_atom_data_table (struct smu_context*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int smu_v11_0_get_vbios_bootup_values(struct smu_context *smu)
{
	int ret, index;
	uint16_t size;
	uint8_t frev, crev;
	struct atom_common_table_header *header;
	struct atom_firmware_info_v3_3 *v_3_3;
	struct atom_firmware_info_v3_1 *v_3_1;

	index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
					    firmwareinfo);

	ret = smu_get_atom_data_table(smu, index, &size, &frev, &crev,
				      (uint8_t **)&header);
	if (ret)
		return ret;

	if (header->format_revision != 3) {
		pr_err("unknown atom_firmware_info version! for smu11\n");
		return -EINVAL;
	}

	switch (header->content_revision) {
	case 0:
	case 1:
	case 2:
		v_3_1 = (struct atom_firmware_info_v3_1 *)header;
		smu->smu_table.boot_values.revision = v_3_1->firmware_revision;
		smu->smu_table.boot_values.gfxclk = v_3_1->bootup_sclk_in10khz;
		smu->smu_table.boot_values.uclk = v_3_1->bootup_mclk_in10khz;
		smu->smu_table.boot_values.socclk = 0;
		smu->smu_table.boot_values.dcefclk = 0;
		smu->smu_table.boot_values.vddc = v_3_1->bootup_vddc_mv;
		smu->smu_table.boot_values.vddci = v_3_1->bootup_vddci_mv;
		smu->smu_table.boot_values.mvddc = v_3_1->bootup_mvddc_mv;
		smu->smu_table.boot_values.vdd_gfx = v_3_1->bootup_vddgfx_mv;
		smu->smu_table.boot_values.cooling_id = v_3_1->coolingsolution_id;
		smu->smu_table.boot_values.pp_table_id = 0;
		break;
	case 3:
	default:
		v_3_3 = (struct atom_firmware_info_v3_3 *)header;
		smu->smu_table.boot_values.revision = v_3_3->firmware_revision;
		smu->smu_table.boot_values.gfxclk = v_3_3->bootup_sclk_in10khz;
		smu->smu_table.boot_values.uclk = v_3_3->bootup_mclk_in10khz;
		smu->smu_table.boot_values.socclk = 0;
		smu->smu_table.boot_values.dcefclk = 0;
		smu->smu_table.boot_values.vddc = v_3_3->bootup_vddc_mv;
		smu->smu_table.boot_values.vddci = v_3_3->bootup_vddci_mv;
		smu->smu_table.boot_values.mvddc = v_3_3->bootup_mvddc_mv;
		smu->smu_table.boot_values.vdd_gfx = v_3_3->bootup_vddgfx_mv;
		smu->smu_table.boot_values.cooling_id = v_3_3->coolingsolution_id;
		smu->smu_table.boot_values.pp_table_id = v_3_3->pplib_pptable_id;
	}

	smu->smu_table.boot_values.format_revision = header->format_revision;
	smu->smu_table.boot_values.content_revision = header->content_revision;

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  mem_refclk_10khz; } ;
union umc_info {TYPE_5__ v31; } ;
struct TYPE_10__ {int /*<<< orphan*/  core_refclk_10khz; } ;
union smu_info {TYPE_4__ v31; } ;
struct TYPE_9__ {int /*<<< orphan*/  firmware_capability; int /*<<< orphan*/  bootup_mclk_in10khz; int /*<<< orphan*/  bootup_sclk_in10khz; } ;
union firmware_info {TYPE_3__ v31; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct amdgpu_pll {int min_post_div; int max_post_div; int min_ref_div; int max_ref_div; int min_feedback_div; int max_feedback_div; scalar_t__ best_vco; scalar_t__ reference_div; void* reference_freq; } ;
struct amdgpu_mode_info {TYPE_6__* atom_context; void* firmware_flags; } ;
struct TYPE_8__ {void* default_mclk; void* default_sclk; struct amdgpu_pll mpll; struct amdgpu_pll spll; } ;
struct TYPE_7__ {void* current_mclk; void* current_sclk; } ;
struct amdgpu_device {struct amdgpu_mode_info mode_info; TYPE_2__ clock; TYPE_1__ pm; } ;
struct TYPE_12__ {scalar_t__ bios; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_6__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int /*<<< orphan*/  firmwareinfo ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_info ; 
 int /*<<< orphan*/  umc_info ; 

int amdgpu_atomfirmware_get_clock_info(struct amdgpu_device *adev)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	struct amdgpu_pll *spll = &adev->clock.spll;
	struct amdgpu_pll *mpll = &adev->clock.mpll;
	uint8_t frev, crev;
	uint16_t data_offset;
	int ret = -EINVAL, index;

	index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
					    firmwareinfo);
	if (amdgpu_atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		union firmware_info *firmware_info =
			(union firmware_info *)(mode_info->atom_context->bios +
						data_offset);

		adev->clock.default_sclk =
			le32_to_cpu(firmware_info->v31.bootup_sclk_in10khz);
		adev->clock.default_mclk =
			le32_to_cpu(firmware_info->v31.bootup_mclk_in10khz);

		adev->pm.current_sclk = adev->clock.default_sclk;
		adev->pm.current_mclk = adev->clock.default_mclk;

		/* not technically a clock, but... */
		adev->mode_info.firmware_flags =
			le32_to_cpu(firmware_info->v31.firmware_capability);

		ret = 0;
	}

	index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
					    smu_info);
	if (amdgpu_atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		union smu_info *smu_info =
			(union smu_info *)(mode_info->atom_context->bios +
					   data_offset);

		/* system clock */
		spll->reference_freq = le32_to_cpu(smu_info->v31.core_refclk_10khz);

		spll->reference_div = 0;
		spll->min_post_div = 1;
		spll->max_post_div = 1;
		spll->min_ref_div = 2;
		spll->max_ref_div = 0xff;
		spll->min_feedback_div = 4;
		spll->max_feedback_div = 0xff;
		spll->best_vco = 0;

		ret = 0;
	}

	index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
					    umc_info);
	if (amdgpu_atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		union umc_info *umc_info =
			(union umc_info *)(mode_info->atom_context->bios +
					   data_offset);

		/* memory clock */
		mpll->reference_freq = le32_to_cpu(umc_info->v31.mem_refclk_10khz);

		mpll->reference_div = 0;
		mpll->min_post_div = 1;
		mpll->max_post_div = 1;
		mpll->min_ref_div = 2;
		mpll->max_ref_div = 0xff;
		mpll->min_feedback_div = 4;
		mpll->max_feedback_div = 0xff;
		mpll->best_vco = 0;

		ret = 0;
	}

	return ret;
}
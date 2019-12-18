#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_debug_params_spmu {int event_types_num; int* event_types; } ;
struct hl_debug_params {size_t reg_idx; int* output; int output_size; struct hl_debug_params_spmu* input; scalar_t__ enable; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int CFG_BASE ; 
 int EINVAL ; 
 int RREG32 (int) ; 
 int SPMU_EVENT_TYPES_OFFSET ; 
 int SPMU_MAX_COUNTERS ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int* debug_spmu_regs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int goya_config_spmu(struct hl_device *hdev,
		struct hl_debug_params *params)
{
	u64 base_reg;
	struct hl_debug_params_spmu *input = params->input;
	u64 *output;
	u32 output_arr_len;
	u32 events_num;
	u32 overflow_idx;
	u32 cycle_cnt_idx;
	int i;

	if (params->reg_idx >= ARRAY_SIZE(debug_spmu_regs)) {
		dev_err(hdev->dev, "Invalid register index in SPMU\n");
		return -EINVAL;
	}

	base_reg = debug_spmu_regs[params->reg_idx] - CFG_BASE;

	if (params->enable) {
		input = params->input;

		if (!input)
			return -EINVAL;

		if (input->event_types_num < 3) {
			dev_err(hdev->dev,
				"not enough event types values for SPMU enable\n");
			return -EINVAL;
		}

		if (input->event_types_num > SPMU_MAX_COUNTERS) {
			dev_err(hdev->dev,
				"too many event types values for SPMU enable\n");
			return -EINVAL;
		}

		WREG32(base_reg + 0xE04, 0x41013046);
		WREG32(base_reg + 0xE04, 0x41013040);

		for (i = 0 ; i < input->event_types_num ; i++)
			WREG32(base_reg + SPMU_EVENT_TYPES_OFFSET + i * 4,
				input->event_types[i]);

		WREG32(base_reg + 0xE04, 0x41013041);
		WREG32(base_reg + 0xC00, 0x8000003F);
	} else {
		output = params->output;
		output_arr_len = params->output_size / 8;
		events_num = output_arr_len - 2;
		overflow_idx = output_arr_len - 2;
		cycle_cnt_idx = output_arr_len - 1;

		if (!output)
			return -EINVAL;

		if (output_arr_len < 3) {
			dev_err(hdev->dev,
				"not enough values for SPMU disable\n");
			return -EINVAL;
		}

		if (events_num > SPMU_MAX_COUNTERS) {
			dev_err(hdev->dev,
				"too many events values for SPMU disable\n");
			return -EINVAL;
		}

		WREG32(base_reg + 0xE04, 0x41013040);

		for (i = 0 ; i < events_num ; i++)
			output[i] = RREG32(base_reg + i * 8);

		output[overflow_idx] = RREG32(base_reg + 0xCC0);

		output[cycle_cnt_idx] = RREG32(base_reg + 0xFC);
		output[cycle_cnt_idx] <<= 32;
		output[cycle_cnt_idx] |= RREG32(base_reg + 0xF8);

		WREG32(base_reg + 0xCC0, 0);
	}

	return 0;
}
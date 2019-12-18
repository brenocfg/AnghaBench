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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_debug_params_bmon {int bw_win; int win_capture; int id; int /*<<< orphan*/  addr_mask1; int /*<<< orphan*/  start_addr1; int /*<<< orphan*/  addr_mask0; int /*<<< orphan*/  start_addr0; } ;
struct hl_debug_params {size_t reg_idx; struct hl_debug_params_bmon* input; scalar_t__ enable; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ CFG_BASE ; 
 int EINVAL ; 
 size_t GOYA_BMON_PCIE_MSTR_RD ; 
 size_t GOYA_BMON_PCIE_MSTR_WR ; 
 size_t GOYA_BMON_PCIE_SLV_RD ; 
 size_t GOYA_BMON_PCIE_SLV_WR ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__* debug_bmon_regs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_config_bmon(struct hl_device *hdev,
		struct hl_debug_params *params)
{
	struct hl_debug_params_bmon *input;
	u64 base_reg;
	u32 pcie_base = 0;

	if (params->reg_idx >= ARRAY_SIZE(debug_bmon_regs)) {
		dev_err(hdev->dev, "Invalid register index in BMON\n");
		return -EINVAL;
	}

	base_reg = debug_bmon_regs[params->reg_idx] - CFG_BASE;

	WREG32(base_reg + 0x104, 1);

	if (params->enable) {
		input = params->input;

		if (!input)
			return -EINVAL;

		WREG32(base_reg + 0x200, lower_32_bits(input->start_addr0));
		WREG32(base_reg + 0x204, upper_32_bits(input->start_addr0));
		WREG32(base_reg + 0x208, lower_32_bits(input->addr_mask0));
		WREG32(base_reg + 0x20C, upper_32_bits(input->addr_mask0));
		WREG32(base_reg + 0x240, lower_32_bits(input->start_addr1));
		WREG32(base_reg + 0x244, upper_32_bits(input->start_addr1));
		WREG32(base_reg + 0x248, lower_32_bits(input->addr_mask1));
		WREG32(base_reg + 0x24C, upper_32_bits(input->addr_mask1));
		WREG32(base_reg + 0x224, 0);
		WREG32(base_reg + 0x234, 0);
		WREG32(base_reg + 0x30C, input->bw_win);
		WREG32(base_reg + 0x308, input->win_capture);

		/* PCIE IF BMON bug WA */
		if (params->reg_idx != GOYA_BMON_PCIE_MSTR_RD &&
				params->reg_idx != GOYA_BMON_PCIE_MSTR_WR &&
				params->reg_idx != GOYA_BMON_PCIE_SLV_RD &&
				params->reg_idx != GOYA_BMON_PCIE_SLV_WR)
			pcie_base = 0xA000000;

		WREG32(base_reg + 0x700, pcie_base | 0xB00 | (input->id << 12));
		WREG32(base_reg + 0x708, pcie_base | 0xA00 | (input->id << 12));
		WREG32(base_reg + 0x70C, pcie_base | 0xC00 | (input->id << 12));

		WREG32(base_reg + 0x100, 0x11);
		WREG32(base_reg + 0x304, 0x1);
	} else {
		WREG32(base_reg + 0x200, 0);
		WREG32(base_reg + 0x204, 0);
		WREG32(base_reg + 0x208, 0xFFFFFFFF);
		WREG32(base_reg + 0x20C, 0xFFFFFFFF);
		WREG32(base_reg + 0x240, 0);
		WREG32(base_reg + 0x244, 0);
		WREG32(base_reg + 0x248, 0xFFFFFFFF);
		WREG32(base_reg + 0x24C, 0xFFFFFFFF);
		WREG32(base_reg + 0x224, 0xFFFFFFFF);
		WREG32(base_reg + 0x234, 0x1070F);
		WREG32(base_reg + 0x30C, 0);
		WREG32(base_reg + 0x308, 0xFFFF);
		WREG32(base_reg + 0x700, 0xA000B00);
		WREG32(base_reg + 0x708, 0xA000A00);
		WREG32(base_reg + 0x70C, 0xA000C00);
		WREG32(base_reg + 0x100, 1);
		WREG32(base_reg + 0x304, 0);
		WREG32(base_reg + 0x104, 0);
	}

	return 0;
}
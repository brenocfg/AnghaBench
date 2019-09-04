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
typedef  int uint32_t ;
struct amdgpu_device {scalar_t__ asic_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_STONEY ; 
 int RLC_SERDES_WR_CTRL__BPM_ADDR__SHIFT ; 
 int RLC_SERDES_WR_CTRL__BPM_DATA_MASK ; 
 int RLC_SERDES_WR_CTRL__BPM_DATA__SHIFT ; 
 int RLC_SERDES_WR_CTRL__P1_SELECT_MASK ; 
 int RLC_SERDES_WR_CTRL__P2_SELECT_MASK ; 
 int RLC_SERDES_WR_CTRL__POWER_DOWN_MASK ; 
 int RLC_SERDES_WR_CTRL__POWER_UP_MASK ; 
 int RLC_SERDES_WR_CTRL__RDDATA_RESET_MASK ; 
 int RLC_SERDES_WR_CTRL__READ_COMMAND_MASK ; 
 int RLC_SERDES_WR_CTRL__REG_ADDR_MASK ; 
 int RLC_SERDES_WR_CTRL__REG_ADDR__SHIFT ; 
 int RLC_SERDES_WR_CTRL__RSVD_BPM_ADDR_MASK ; 
 int RLC_SERDES_WR_CTRL__SHORT_FORMAT_MASK ; 
 int RLC_SERDES_WR_CTRL__SRBM_OVERRIDE_MASK ; 
 int RLC_SERDES_WR_CTRL__WRITE_COMMAND_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v8_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  mmRLC_SERDES_WR_CTRL ; 
 int /*<<< orphan*/  mmRLC_SERDES_WR_CU_MASTER_MASK ; 
 int /*<<< orphan*/  mmRLC_SERDES_WR_NONCU_MASTER_MASK ; 

__attribute__((used)) static void gfx_v8_0_send_serdes_cmd(struct amdgpu_device *adev,
				     uint32_t reg_addr, uint32_t cmd)
{
	uint32_t data;

	gfx_v8_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);

	WREG32(mmRLC_SERDES_WR_CU_MASTER_MASK, 0xffffffff);
	WREG32(mmRLC_SERDES_WR_NONCU_MASTER_MASK, 0xffffffff);

	data = RREG32(mmRLC_SERDES_WR_CTRL);
	if (adev->asic_type == CHIP_STONEY)
		data &= ~(RLC_SERDES_WR_CTRL__WRITE_COMMAND_MASK |
			  RLC_SERDES_WR_CTRL__READ_COMMAND_MASK |
			  RLC_SERDES_WR_CTRL__P1_SELECT_MASK |
			  RLC_SERDES_WR_CTRL__P2_SELECT_MASK |
			  RLC_SERDES_WR_CTRL__RDDATA_RESET_MASK |
			  RLC_SERDES_WR_CTRL__POWER_DOWN_MASK |
			  RLC_SERDES_WR_CTRL__POWER_UP_MASK |
			  RLC_SERDES_WR_CTRL__SHORT_FORMAT_MASK |
			  RLC_SERDES_WR_CTRL__SRBM_OVERRIDE_MASK);
	else
		data &= ~(RLC_SERDES_WR_CTRL__WRITE_COMMAND_MASK |
			  RLC_SERDES_WR_CTRL__READ_COMMAND_MASK |
			  RLC_SERDES_WR_CTRL__P1_SELECT_MASK |
			  RLC_SERDES_WR_CTRL__P2_SELECT_MASK |
			  RLC_SERDES_WR_CTRL__RDDATA_RESET_MASK |
			  RLC_SERDES_WR_CTRL__POWER_DOWN_MASK |
			  RLC_SERDES_WR_CTRL__POWER_UP_MASK |
			  RLC_SERDES_WR_CTRL__SHORT_FORMAT_MASK |
			  RLC_SERDES_WR_CTRL__BPM_DATA_MASK |
			  RLC_SERDES_WR_CTRL__REG_ADDR_MASK |
			  RLC_SERDES_WR_CTRL__SRBM_OVERRIDE_MASK);
	data |= (RLC_SERDES_WR_CTRL__RSVD_BPM_ADDR_MASK |
		 (cmd << RLC_SERDES_WR_CTRL__BPM_DATA__SHIFT) |
		 (reg_addr << RLC_SERDES_WR_CTRL__REG_ADDR__SHIFT) |
		 (0xff << RLC_SERDES_WR_CTRL__BPM_ADDR__SHIFT));

	WREG32(mmRLC_SERDES_WR_CTRL, data);
}
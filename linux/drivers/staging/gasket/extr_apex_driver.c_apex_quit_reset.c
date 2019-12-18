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
typedef  int /*<<< orphan*/  u32 ;
struct gasket_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APEX_BAR2_REG_SCU_2 ; 
 int /*<<< orphan*/  APEX_BAR2_REG_SCU_3 ; 
 int /*<<< orphan*/  APEX_BAR_INDEX ; 
 int APEX_RESET_DELAY ; 
 int APEX_RESET_RETRY ; 
 int /*<<< orphan*/  BIT (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SCU3_CUR_RST_GCB_BIT_MASK ; 
 int SCU3_RG_PWR_STATE_OVR_BIT_OFFSET ; 
 int SCU3_RG_PWR_STATE_OVR_MASK_WIDTH ; 
 int /*<<< orphan*/  allow_hw_clock_gating ; 
 scalar_t__ bypass_top_level ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gasket_dev_read_32 (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gasket_read_modify_write_32 (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ gasket_wait_with_reschedule (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int apex_quit_reset(struct gasket_dev *gasket_dev)
{
	u32 val0, val1;

	if (bypass_top_level)
		return 0;

	/*
	 * Disable sleep mode:
	 *  - Disable GCB memory shut down:
	 *    - b00: Not forced (HW controlled)
	 *    - b1x: Force disable
	 */
	gasket_read_modify_write_32(gasket_dev, APEX_BAR_INDEX,
				    APEX_BAR2_REG_SCU_3, 0x0, 2, 14);

	/*
	 *  - Disable software clock gate:
	 *    - b00: Not forced (HW controlled)
	 *    - b1x: Force disable
	 */
	gasket_read_modify_write_32(gasket_dev, APEX_BAR_INDEX,
				    APEX_BAR2_REG_SCU_2, 0x0, 2, 18);

	/*
	 *  - Disable GCB reset (rg_rst_gcb):
	 *    - b00: Not forced (HW controlled)
	 *    - b1x: Force disable = Force not Reset
	 */
	gasket_read_modify_write_32(gasket_dev, APEX_BAR_INDEX,
				    APEX_BAR2_REG_SCU_2, 0x2, 2, 2);

	/*    - Wait for RAM enable. */
	if (gasket_wait_with_reschedule(gasket_dev, APEX_BAR_INDEX,
					APEX_BAR2_REG_SCU_3, BIT(6), 0,
					APEX_RESET_DELAY, APEX_RESET_RETRY)) {
		dev_err(gasket_dev->dev,
			"RAM did not enable within timeout (%d ms)\n",
			APEX_RESET_RETRY * APEX_RESET_DELAY);
		return -ETIMEDOUT;
	}

	/*    - Wait for Reset complete. */
	if (gasket_wait_with_reschedule(gasket_dev, APEX_BAR_INDEX,
					APEX_BAR2_REG_SCU_3,
					SCU3_CUR_RST_GCB_BIT_MASK, 0,
					APEX_RESET_DELAY, APEX_RESET_RETRY)) {
		dev_err(gasket_dev->dev,
			"GCB did not leave reset within timeout (%d ms)\n",
			APEX_RESET_RETRY * APEX_RESET_DELAY);
		return -ETIMEDOUT;
	}

	if (!allow_hw_clock_gating) {
		val0 = gasket_dev_read_32(gasket_dev, APEX_BAR_INDEX,
					  APEX_BAR2_REG_SCU_3);
		/* Inactive and Sleep mode are disabled. */
		gasket_read_modify_write_32(gasket_dev,
					    APEX_BAR_INDEX,
					    APEX_BAR2_REG_SCU_3, 0x3,
					    SCU3_RG_PWR_STATE_OVR_MASK_WIDTH,
					    SCU3_RG_PWR_STATE_OVR_BIT_OFFSET);
		val1 = gasket_dev_read_32(gasket_dev, APEX_BAR_INDEX,
					  APEX_BAR2_REG_SCU_3);
		dev_dbg(gasket_dev->dev,
			"Disallow HW clock gating 0x%x -> 0x%x\n", val0, val1);
	} else {
		val0 = gasket_dev_read_32(gasket_dev, APEX_BAR_INDEX,
					  APEX_BAR2_REG_SCU_3);
		/* Inactive mode enabled - Sleep mode disabled. */
		gasket_read_modify_write_32(gasket_dev, APEX_BAR_INDEX,
					    APEX_BAR2_REG_SCU_3, 2,
					    SCU3_RG_PWR_STATE_OVR_MASK_WIDTH,
					    SCU3_RG_PWR_STATE_OVR_BIT_OFFSET);
		val1 = gasket_dev_read_32(gasket_dev, APEX_BAR_INDEX,
					  APEX_BAR2_REG_SCU_3);
		dev_dbg(gasket_dev->dev, "Allow HW clock gating 0x%x -> 0x%x\n",
			val0, val1);
	}

	return 0;
}
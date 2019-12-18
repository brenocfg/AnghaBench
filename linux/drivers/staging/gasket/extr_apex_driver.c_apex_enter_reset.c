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
struct gasket_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APEX_BAR2_REG_IDLEGENERATOR_IDLEGEN_IDLEREGISTER ; 
 int /*<<< orphan*/  APEX_BAR2_REG_SCU_2 ; 
 int /*<<< orphan*/  APEX_BAR2_REG_SCU_3 ; 
 int /*<<< orphan*/  APEX_BAR2_REG_USER_HIB_DMA_PAUSE ; 
 int /*<<< orphan*/  APEX_BAR2_REG_USER_HIB_DMA_PAUSED ; 
 int /*<<< orphan*/  APEX_BAR_INDEX ; 
 int APEX_RESET_DELAY ; 
 int APEX_RESET_RETRY ; 
 int BIT (int) ; 
 int ETIMEDOUT ; 
 scalar_t__ bypass_top_level ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gasket_dev_write_64 (struct gasket_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gasket_read_modify_write_32 (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  gasket_read_modify_write_64 (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ gasket_wait_with_reschedule (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int apex_enter_reset(struct gasket_dev *gasket_dev)
{
	if (bypass_top_level)
		return 0;

	/*
	 * Software reset:
	 * Enable sleep mode
	 *  - Software force GCB idle
	 *    - Enable GCB idle
	 */
	gasket_read_modify_write_64(gasket_dev, APEX_BAR_INDEX,
				    APEX_BAR2_REG_IDLEGENERATOR_IDLEGEN_IDLEREGISTER,
				    0x0, 1, 32);

	/*    - Initiate DMA pause */
	gasket_dev_write_64(gasket_dev, 1, APEX_BAR_INDEX,
			    APEX_BAR2_REG_USER_HIB_DMA_PAUSE);

	/*    - Wait for DMA pause complete. */
	if (gasket_wait_with_reschedule(gasket_dev, APEX_BAR_INDEX,
					APEX_BAR2_REG_USER_HIB_DMA_PAUSED, 1, 1,
					APEX_RESET_DELAY, APEX_RESET_RETRY)) {
		dev_err(gasket_dev->dev,
			"DMAs did not quiesce within timeout (%d ms)\n",
			APEX_RESET_RETRY * APEX_RESET_DELAY);
		return -ETIMEDOUT;
	}

	/*  - Enable GCB reset (0x1 to rg_rst_gcb) */
	gasket_read_modify_write_32(gasket_dev, APEX_BAR_INDEX,
				    APEX_BAR2_REG_SCU_2, 0x1, 2, 2);

	/*  - Enable GCB clock Gate (0x1 to rg_gated_gcb) */
	gasket_read_modify_write_32(gasket_dev, APEX_BAR_INDEX,
				    APEX_BAR2_REG_SCU_2, 0x1, 2, 18);

	/*  - Enable GCB memory shut down (0x3 to rg_force_ram_sd) */
	gasket_read_modify_write_32(gasket_dev, APEX_BAR_INDEX,
				    APEX_BAR2_REG_SCU_3, 0x3, 2, 14);

	/*    - Wait for RAM shutdown. */
	if (gasket_wait_with_reschedule(gasket_dev, APEX_BAR_INDEX,
					APEX_BAR2_REG_SCU_3, BIT(6), BIT(6),
					APEX_RESET_DELAY, APEX_RESET_RETRY)) {
		dev_err(gasket_dev->dev,
			"RAM did not shut down within timeout (%d ms)\n",
			APEX_RESET_RETRY * APEX_RESET_DELAY);
		return -ETIMEDOUT;
	}

	return 0;
}
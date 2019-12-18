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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHECKER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAR (int,int) ; 
 int /*<<< orphan*/  VAR8 (int,int) ; 
 int /*<<< orphan*/  mt9t112_auto_focus_setting (struct i2c_client const*) ; 
 int /*<<< orphan*/  mt9t112_init_pll (struct i2c_client const*) ; 
 int /*<<< orphan*/  mt9t112_init_setting (struct i2c_client const*) ; 
 int /*<<< orphan*/  mt9t112_mcu_write (int,struct i2c_client const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt9t112_reg_mask_set (int,struct i2c_client const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9t112_reg_write (int,struct i2c_client const*,int,int) ; 
 int /*<<< orphan*/  mt9t112_reset (struct i2c_client const*) ; 

__attribute__((used)) static int mt9t112_init_camera(const struct i2c_client *client)
{
	int ret;

	ECHECKER(ret, mt9t112_reset(client));
	ECHECKER(ret, mt9t112_init_pll(client));
	ECHECKER(ret, mt9t112_init_setting(client));
	ECHECKER(ret, mt9t112_auto_focus_setting(client));

	mt9t112_reg_mask_set(ret, client, 0x0018, 0x0004, 0);

	/* Analog setting B.*/
	mt9t112_reg_write(ret, client, 0x3084, 0x2409);
	mt9t112_reg_write(ret, client, 0x3092, 0x0A49);
	mt9t112_reg_write(ret, client, 0x3094, 0x4949);
	mt9t112_reg_write(ret, client, 0x3096, 0x4950);

	/*
	 * Disable adaptive clock.
	 * PRI_A_CONFIG_JPEG_OB_TX_CONTROL_VAR
	 * PRI_B_CONFIG_JPEG_OB_TX_CONTROL_VAR
	 */
	mt9t112_mcu_write(ret, client, VAR(26, 160), 0x0A2E);
	mt9t112_mcu_write(ret, client, VAR(27, 160), 0x0A2E);

	/*
	 * Configure Status in Status_before_length Format and enable header.
	 * PRI_B_CONFIG_JPEG_OB_TX_CONTROL_VAR
	 */
	mt9t112_mcu_write(ret, client, VAR(27, 144), 0x0CB4);

	/*
	 * Enable JPEG in context B.
	 * PRI_B_CONFIG_JPEG_OB_TX_CONTROL_VAR
	 */
	mt9t112_mcu_write(ret, client, VAR8(27, 142), 0x01);

	/* Disable Dac_TXLO. */
	mt9t112_reg_write(ret, client, 0x316C, 0x350F);

	/* Set max slew rates. */
	mt9t112_reg_write(ret, client, 0x1E, 0x777);

	return ret;
}
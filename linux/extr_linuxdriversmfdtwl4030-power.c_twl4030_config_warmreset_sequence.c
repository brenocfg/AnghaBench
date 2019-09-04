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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  PWR_ENABLE_WARMRESET ; 
 int /*<<< orphan*/  R_P1_SW_EVENTS ; 
 int /*<<< orphan*/  R_P2_SW_EVENTS ; 
 int /*<<< orphan*/  R_P3_SW_EVENTS ; 
 int /*<<< orphan*/  R_SEQ_ADD_WARM ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_config_warmreset_sequence(u8 address)
{
	int err;
	u8 rd_data;

	/* Set WARM RESET SEQ address for P1 */
	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, address, R_SEQ_ADD_WARM);
	if (err)
		goto out;

	/* P1/P2/P3 enable WARMRESET */
	err = twl_i2c_read_u8(TWL_MODULE_PM_MASTER, &rd_data, R_P1_SW_EVENTS);
	if (err)
		goto out;

	rd_data |= PWR_ENABLE_WARMRESET;
	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, rd_data, R_P1_SW_EVENTS);
	if (err)
		goto out;

	err = twl_i2c_read_u8(TWL_MODULE_PM_MASTER, &rd_data, R_P2_SW_EVENTS);
	if (err)
		goto out;

	rd_data |= PWR_ENABLE_WARMRESET;
	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, rd_data, R_P2_SW_EVENTS);
	if (err)
		goto out;

	err = twl_i2c_read_u8(TWL_MODULE_PM_MASTER, &rd_data, R_P3_SW_EVENTS);
	if (err)
		goto out;

	rd_data |= PWR_ENABLE_WARMRESET;
	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, rd_data, R_P3_SW_EVENTS);
out:
	if (err)
		pr_err("TWL4030 warmreset seq config error\n");
	return err;
}
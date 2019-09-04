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
struct twl4030_power_data {scalar_t__ ac_charger_quirk; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWR_LVL_WAKEUP ; 
 int /*<<< orphan*/  R_CFG_P1_TRANSITION ; 
 int /*<<< orphan*/  R_P1_SW_EVENTS ; 
 int /*<<< orphan*/  R_P2_SW_EVENTS ; 
 int /*<<< orphan*/  R_SEQ_ADD_S2A12 ; 
 int /*<<< orphan*/  STARTON_CHG ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 scalar_t__ machine_is_omap_3430sdp () ; 
 scalar_t__ machine_is_omap_ldp () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
twl4030_config_wakeup12_sequence(const struct twl4030_power_data *pdata,
				 u8 address)
{
	int err = 0;
	u8 data;

	/* Set SLEEP to ACTIVE SEQ address for P1 and P2 */
	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, address, R_SEQ_ADD_S2A12);
	if (err)
		goto out;

	/* P1/P2 LVL_WAKEUP should be on LEVEL */
	err = twl_i2c_read_u8(TWL_MODULE_PM_MASTER, &data, R_P1_SW_EVENTS);
	if (err)
		goto out;

	data |= PWR_LVL_WAKEUP;
	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, data, R_P1_SW_EVENTS);
	if (err)
		goto out;

	err = twl_i2c_read_u8(TWL_MODULE_PM_MASTER, &data, R_P2_SW_EVENTS);
	if (err)
		goto out;

	data |= PWR_LVL_WAKEUP;
	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, data, R_P2_SW_EVENTS);
	if (err)
		goto out;

	if (pdata->ac_charger_quirk || machine_is_omap_3430sdp() ||
	    machine_is_omap_ldp()) {
		/* Disabling AC charger effect on sleep-active transitions */
		err = twl_i2c_read_u8(TWL_MODULE_PM_MASTER, &data,
				      R_CFG_P1_TRANSITION);
		if (err)
			goto out;
		data &= ~STARTON_CHG;
		err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, data,
				       R_CFG_P1_TRANSITION);
		if (err)
			goto out;
	}

out:
	if (err)
		pr_err("TWL4030 wakeup sequence for P1 and P2" \
			"config error\n");
	return err;
}
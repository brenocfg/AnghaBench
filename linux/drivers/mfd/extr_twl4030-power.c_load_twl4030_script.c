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
typedef  scalar_t__ u8 ;
struct twl4030_script {scalar_t__ size; int flags; int /*<<< orphan*/  script; } ;
struct twl4030_power_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ END_OF_SCRIPT ; 
 int /*<<< orphan*/  R_SEQ_ADD_A2S ; 
 int TWL4030_SLEEP_SCRIPT ; 
 int TWL4030_WAKEUP12_SCRIPT ; 
 int TWL4030_WAKEUP3_SCRIPT ; 
 int TWL4030_WRST_SCRIPT ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int twl4030_config_sleep_sequence (scalar_t__) ; 
 int twl4030_config_wakeup12_sequence (struct twl4030_power_data const*,scalar_t__) ; 
 int twl4030_config_wakeup3_sequence (scalar_t__) ; 
 int twl4030_config_warmreset_sequence (scalar_t__) ; 
 int twl4030_write_script (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_twl4030_script(const struct twl4030_power_data *pdata,
			       struct twl4030_script *tscript,
			       u8 address)
{
	int err;
	static int order;

	/* Make sure the script isn't going beyond last valid address (0x3f) */
	if ((address + tscript->size) > END_OF_SCRIPT) {
		pr_err("TWL4030 scripts too big error\n");
		return -EINVAL;
	}

	err = twl4030_write_script(address, tscript->script, tscript->size);
	if (err)
		goto out;

	if (tscript->flags & TWL4030_WRST_SCRIPT) {
		err = twl4030_config_warmreset_sequence(address);
		if (err)
			goto out;
	}
	if (tscript->flags & TWL4030_WAKEUP12_SCRIPT) {
		/* Reset any existing sleep script to avoid hangs on reboot */
		err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, END_OF_SCRIPT,
				       R_SEQ_ADD_A2S);
		if (err)
			goto out;

		err = twl4030_config_wakeup12_sequence(pdata, address);
		if (err)
			goto out;
		order = 1;
	}
	if (tscript->flags & TWL4030_WAKEUP3_SCRIPT) {
		err = twl4030_config_wakeup3_sequence(address);
		if (err)
			goto out;
	}
	if (tscript->flags & TWL4030_SLEEP_SCRIPT) {
		if (!order)
			pr_warn("TWL4030: Bad order of scripts (sleep script before wakeup) Leads to boot failure on some boards\n");
		err = twl4030_config_sleep_sequence(address);
	}
out:
	return err;
}
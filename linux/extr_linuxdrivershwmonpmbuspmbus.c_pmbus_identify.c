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
struct pmbus_driver_info {int pages; scalar_t__* format; int /*<<< orphan*/  vrm_version; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PMBUS_PAGE ; 
 int PMBUS_PAGES ; 
 int /*<<< orphan*/  PMBUS_VOUT_MODE ; 
 size_t PSC_VOLTAGE_OUT ; 
 scalar_t__ direct ; 
 scalar_t__ pmbus_check_byte_register (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmbus_clear_faults (struct i2c_client*) ; 
 int /*<<< orphan*/  pmbus_find_sensor_groups (struct i2c_client*,struct pmbus_driver_info*) ; 
 int pmbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pmbus_set_page (struct i2c_client*,int) ; 
 scalar_t__ vid ; 
 int /*<<< orphan*/  vr11 ; 

__attribute__((used)) static int pmbus_identify(struct i2c_client *client,
			  struct pmbus_driver_info *info)
{
	int ret = 0;

	if (!info->pages) {
		/*
		 * Check if the PAGE command is supported. If it is,
		 * keep setting the page number until it fails or until the
		 * maximum number of pages has been reached. Assume that
		 * this is the number of pages supported by the chip.
		 */
		if (pmbus_check_byte_register(client, 0, PMBUS_PAGE)) {
			int page;

			for (page = 1; page < PMBUS_PAGES; page++) {
				if (pmbus_set_page(client, page) < 0)
					break;
			}
			pmbus_set_page(client, 0);
			info->pages = page;
		} else {
			info->pages = 1;
		}

		pmbus_clear_faults(client);
	}

	if (pmbus_check_byte_register(client, 0, PMBUS_VOUT_MODE)) {
		int vout_mode;

		vout_mode = pmbus_read_byte_data(client, 0, PMBUS_VOUT_MODE);
		if (vout_mode >= 0 && vout_mode != 0xff) {
			switch (vout_mode >> 5) {
			case 0:
				break;
			case 1:
				info->format[PSC_VOLTAGE_OUT] = vid;
				info->vrm_version = vr11;
				break;
			case 2:
				info->format[PSC_VOLTAGE_OUT] = direct;
				break;
			default:
				ret = -ENODEV;
				goto abort;
			}
		}
	}

	/*
	 * We should check if the COEFFICIENTS register is supported.
	 * If it is, and the chip is configured for direct mode, we can read
	 * the coefficients from the chip, one set per group of sensor
	 * registers.
	 *
	 * To do this, we will need access to a chip which actually supports the
	 * COEFFICIENTS command, since the command is too complex to implement
	 * without testing it. Until then, abort if a chip configured for direct
	 * mode was detected.
	 */
	if (info->format[PSC_VOLTAGE_OUT] == direct) {
		ret = -ENODEV;
		goto abort;
	}

	/* Try to find sensor groups  */
	pmbus_find_sensor_groups(client, info);
abort:
	return ret;
}
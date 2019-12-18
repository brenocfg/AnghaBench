#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pmbus_data {int* exponent; TYPE_1__* info; } ;
struct i2c_client {int dummy; } ;
typedef  int s8 ;
struct TYPE_2__ {int /*<<< orphan*/ * format; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PMBUS_VOUT_MODE ; 
 size_t PSC_VOLTAGE_OUT ; 
 int _pmbus_read_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  direct ; 
 int /*<<< orphan*/  linear ; 
 scalar_t__ pmbus_check_byte_register (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmbus_clear_fault_page (struct i2c_client*,int) ; 
 int /*<<< orphan*/  vid ; 

__attribute__((used)) static int pmbus_identify_common(struct i2c_client *client,
				 struct pmbus_data *data, int page)
{
	int vout_mode = -1;

	if (pmbus_check_byte_register(client, page, PMBUS_VOUT_MODE))
		vout_mode = _pmbus_read_byte_data(client, page,
						  PMBUS_VOUT_MODE);
	if (vout_mode >= 0 && vout_mode != 0xff) {
		/*
		 * Not all chips support the VOUT_MODE command,
		 * so a failure to read it is not an error.
		 */
		switch (vout_mode >> 5) {
		case 0:	/* linear mode      */
			if (data->info->format[PSC_VOLTAGE_OUT] != linear)
				return -ENODEV;

			data->exponent[page] = ((s8)(vout_mode << 3)) >> 3;
			break;
		case 1: /* VID mode         */
			if (data->info->format[PSC_VOLTAGE_OUT] != vid)
				return -ENODEV;
			break;
		case 2:	/* direct mode      */
			if (data->info->format[PSC_VOLTAGE_OUT] != direct)
				return -ENODEV;
			break;
		default:
			return -ENODEV;
		}
	}

	pmbus_clear_fault_page(client, page);
	return 0;
}
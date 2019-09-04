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
struct pmbus_driver_info {int* func; int pages; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMBUS_FAN_CONFIG_12 ; 
 int /*<<< orphan*/  PMBUS_FAN_CONFIG_34 ; 
 int PMBUS_HAVE_FAN12 ; 
 int PMBUS_HAVE_FAN34 ; 
 int PMBUS_HAVE_IIN ; 
 int PMBUS_HAVE_IOUT ; 
 int PMBUS_HAVE_PIN ; 
 int PMBUS_HAVE_POUT ; 
 int PMBUS_HAVE_STATUS_FAN12 ; 
 int PMBUS_HAVE_STATUS_FAN34 ; 
 int PMBUS_HAVE_STATUS_INPUT ; 
 int PMBUS_HAVE_STATUS_IOUT ; 
 int PMBUS_HAVE_STATUS_TEMP ; 
 int PMBUS_HAVE_STATUS_VOUT ; 
 int PMBUS_HAVE_TEMP ; 
 int PMBUS_HAVE_TEMP2 ; 
 int PMBUS_HAVE_TEMP3 ; 
 int PMBUS_HAVE_VCAP ; 
 int PMBUS_HAVE_VIN ; 
 int PMBUS_HAVE_VOUT ; 
 int /*<<< orphan*/  PMBUS_READ_FAN_SPEED_1 ; 
 int /*<<< orphan*/  PMBUS_READ_FAN_SPEED_3 ; 
 int /*<<< orphan*/  PMBUS_READ_IIN ; 
 int /*<<< orphan*/  PMBUS_READ_IOUT ; 
 int /*<<< orphan*/  PMBUS_READ_PIN ; 
 int /*<<< orphan*/  PMBUS_READ_POUT ; 
 int /*<<< orphan*/  PMBUS_READ_TEMPERATURE_1 ; 
 int /*<<< orphan*/  PMBUS_READ_TEMPERATURE_2 ; 
 int /*<<< orphan*/  PMBUS_READ_TEMPERATURE_3 ; 
 int /*<<< orphan*/  PMBUS_READ_VCAP ; 
 int /*<<< orphan*/  PMBUS_READ_VIN ; 
 int /*<<< orphan*/  PMBUS_READ_VOUT ; 
 int /*<<< orphan*/  PMBUS_STATUS_FAN_12 ; 
 int /*<<< orphan*/  PMBUS_STATUS_FAN_34 ; 
 int /*<<< orphan*/  PMBUS_STATUS_INPUT ; 
 int /*<<< orphan*/  PMBUS_STATUS_IOUT ; 
 int /*<<< orphan*/  PMBUS_STATUS_TEMPERATURE ; 
 int /*<<< orphan*/  PMBUS_STATUS_VOUT ; 
 scalar_t__ pmbus_check_byte_register (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pmbus_check_word_register (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmbus_find_sensor_groups(struct i2c_client *client,
				     struct pmbus_driver_info *info)
{
	int page;

	/* Sensors detected on page 0 only */
	if (pmbus_check_word_register(client, 0, PMBUS_READ_VIN))
		info->func[0] |= PMBUS_HAVE_VIN;
	if (pmbus_check_word_register(client, 0, PMBUS_READ_VCAP))
		info->func[0] |= PMBUS_HAVE_VCAP;
	if (pmbus_check_word_register(client, 0, PMBUS_READ_IIN))
		info->func[0] |= PMBUS_HAVE_IIN;
	if (pmbus_check_word_register(client, 0, PMBUS_READ_PIN))
		info->func[0] |= PMBUS_HAVE_PIN;
	if (info->func[0]
	    && pmbus_check_byte_register(client, 0, PMBUS_STATUS_INPUT))
		info->func[0] |= PMBUS_HAVE_STATUS_INPUT;
	if (pmbus_check_byte_register(client, 0, PMBUS_FAN_CONFIG_12) &&
	    pmbus_check_word_register(client, 0, PMBUS_READ_FAN_SPEED_1)) {
		info->func[0] |= PMBUS_HAVE_FAN12;
		if (pmbus_check_byte_register(client, 0, PMBUS_STATUS_FAN_12))
			info->func[0] |= PMBUS_HAVE_STATUS_FAN12;
	}
	if (pmbus_check_byte_register(client, 0, PMBUS_FAN_CONFIG_34) &&
	    pmbus_check_word_register(client, 0, PMBUS_READ_FAN_SPEED_3)) {
		info->func[0] |= PMBUS_HAVE_FAN34;
		if (pmbus_check_byte_register(client, 0, PMBUS_STATUS_FAN_34))
			info->func[0] |= PMBUS_HAVE_STATUS_FAN34;
	}
	if (pmbus_check_word_register(client, 0, PMBUS_READ_TEMPERATURE_1))
		info->func[0] |= PMBUS_HAVE_TEMP;
	if (pmbus_check_word_register(client, 0, PMBUS_READ_TEMPERATURE_2))
		info->func[0] |= PMBUS_HAVE_TEMP2;
	if (pmbus_check_word_register(client, 0, PMBUS_READ_TEMPERATURE_3))
		info->func[0] |= PMBUS_HAVE_TEMP3;
	if (info->func[0] & (PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2
			     | PMBUS_HAVE_TEMP3)
	    && pmbus_check_byte_register(client, 0,
					 PMBUS_STATUS_TEMPERATURE))
			info->func[0] |= PMBUS_HAVE_STATUS_TEMP;

	/* Sensors detected on all pages */
	for (page = 0; page < info->pages; page++) {
		if (pmbus_check_word_register(client, page, PMBUS_READ_VOUT)) {
			info->func[page] |= PMBUS_HAVE_VOUT;
			if (pmbus_check_byte_register(client, page,
						      PMBUS_STATUS_VOUT))
				info->func[page] |= PMBUS_HAVE_STATUS_VOUT;
		}
		if (pmbus_check_word_register(client, page, PMBUS_READ_IOUT)) {
			info->func[page] |= PMBUS_HAVE_IOUT;
			if (pmbus_check_byte_register(client, 0,
						      PMBUS_STATUS_IOUT))
				info->func[page] |= PMBUS_HAVE_STATUS_IOUT;
		}
		if (pmbus_check_word_register(client, page, PMBUS_READ_POUT))
			info->func[page] |= PMBUS_HAVE_POUT;
	}
}
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
 int ENODATA ; 
 int ENXIO ; 
 int /*<<< orphan*/  MAX8688_MFR_IOUT_PEAK ; 
 int /*<<< orphan*/  MAX8688_MFR_TEMPERATURE_PEAK ; 
 int /*<<< orphan*/  MAX8688_MFR_VOUT_PEAK ; 
#define  PMBUS_VIRT_READ_IOUT_MAX 133 
#define  PMBUS_VIRT_READ_TEMP_MAX 132 
#define  PMBUS_VIRT_READ_VOUT_MAX 131 
#define  PMBUS_VIRT_RESET_IOUT_HISTORY 130 
#define  PMBUS_VIRT_RESET_TEMP_HISTORY 129 
#define  PMBUS_VIRT_RESET_VOUT_HISTORY 128 
 int pmbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8688_read_word_data(struct i2c_client *client, int page, int reg)
{
	int ret;

	if (page > 0)
		return -ENXIO;

	switch (reg) {
	case PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_read_word_data(client, 0, MAX8688_MFR_VOUT_PEAK);
		break;
	case PMBUS_VIRT_READ_IOUT_MAX:
		ret = pmbus_read_word_data(client, 0, MAX8688_MFR_IOUT_PEAK);
		break;
	case PMBUS_VIRT_READ_TEMP_MAX:
		ret = pmbus_read_word_data(client, 0,
					   MAX8688_MFR_TEMPERATURE_PEAK);
		break;
	case PMBUS_VIRT_RESET_VOUT_HISTORY:
	case PMBUS_VIRT_RESET_IOUT_HISTORY:
	case PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = 0;
		break;
	default:
		ret = -ENODATA;
		break;
	}
	return ret;
}
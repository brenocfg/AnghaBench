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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  MAX8688_MFR_IOUT_PEAK ; 
 int /*<<< orphan*/  MAX8688_MFR_TEMPERATURE_PEAK ; 
 int /*<<< orphan*/  MAX8688_MFR_VOUT_PEAK ; 
#define  PMBUS_VIRT_RESET_IOUT_HISTORY 130 
#define  PMBUS_VIRT_RESET_TEMP_HISTORY 129 
#define  PMBUS_VIRT_RESET_VOUT_HISTORY 128 
 int pmbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max8688_write_word_data(struct i2c_client *client, int page, int reg,
				   u16 word)
{
	int ret;

	switch (reg) {
	case PMBUS_VIRT_RESET_VOUT_HISTORY:
		ret = pmbus_write_word_data(client, 0, MAX8688_MFR_VOUT_PEAK,
					    0);
		break;
	case PMBUS_VIRT_RESET_IOUT_HISTORY:
		ret = pmbus_write_word_data(client, 0, MAX8688_MFR_IOUT_PEAK,
					    0);
		break;
	case PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = pmbus_write_word_data(client, 0,
					    MAX8688_MFR_TEMPERATURE_PEAK,
					    0xffff);
		break;
	default:
		ret = -ENODATA;
		break;
	}
	return ret;
}
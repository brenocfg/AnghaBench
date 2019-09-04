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
 int /*<<< orphan*/  IR35221_MFR_IOUT_PEAK ; 
 int /*<<< orphan*/  IR35221_MFR_IOUT_VALLEY ; 
 int /*<<< orphan*/  IR35221_MFR_TEMP_PEAK ; 
 int /*<<< orphan*/  IR35221_MFR_TEMP_VALLEY ; 
 int /*<<< orphan*/  IR35221_MFR_VIN_PEAK ; 
 int /*<<< orphan*/  IR35221_MFR_VIN_VALLEY ; 
 int /*<<< orphan*/  IR35221_MFR_VOUT_PEAK ; 
 int /*<<< orphan*/  IR35221_MFR_VOUT_VALLEY ; 
#define  PMBUS_VIRT_READ_IOUT_MAX 135 
#define  PMBUS_VIRT_READ_IOUT_MIN 134 
#define  PMBUS_VIRT_READ_TEMP_MAX 133 
#define  PMBUS_VIRT_READ_TEMP_MIN 132 
#define  PMBUS_VIRT_READ_VIN_MAX 131 
#define  PMBUS_VIRT_READ_VIN_MIN 130 
#define  PMBUS_VIRT_READ_VOUT_MAX 129 
#define  PMBUS_VIRT_READ_VOUT_MIN 128 
 int pmbus_read_word_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ir35221_read_word_data(struct i2c_client *client, int page, int reg)
{
	int ret;

	switch (reg) {
	case PMBUS_VIRT_READ_VIN_MAX:
		ret = pmbus_read_word_data(client, page, IR35221_MFR_VIN_PEAK);
		break;
	case PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_read_word_data(client, page, IR35221_MFR_VOUT_PEAK);
		break;
	case PMBUS_VIRT_READ_IOUT_MAX:
		ret = pmbus_read_word_data(client, page, IR35221_MFR_IOUT_PEAK);
		break;
	case PMBUS_VIRT_READ_TEMP_MAX:
		ret = pmbus_read_word_data(client, page, IR35221_MFR_TEMP_PEAK);
		break;
	case PMBUS_VIRT_READ_VIN_MIN:
		ret = pmbus_read_word_data(client, page,
					   IR35221_MFR_VIN_VALLEY);
		break;
	case PMBUS_VIRT_READ_VOUT_MIN:
		ret = pmbus_read_word_data(client, page,
					   IR35221_MFR_VOUT_VALLEY);
		break;
	case PMBUS_VIRT_READ_IOUT_MIN:
		ret = pmbus_read_word_data(client, page,
					   IR35221_MFR_IOUT_VALLEY);
		break;
	case PMBUS_VIRT_READ_TEMP_MIN:
		ret = pmbus_read_word_data(client, page,
					   IR35221_MFR_TEMP_VALLEY);
		break;
	default:
		ret = -ENODATA;
		break;
	}

	return ret;
}
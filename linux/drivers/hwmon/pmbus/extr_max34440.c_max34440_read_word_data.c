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
struct pmbus_driver_info {int dummy; } ;
struct max34440_data {int /*<<< orphan*/  id; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENXIO ; 
 int /*<<< orphan*/  MAX34440_MFR_IOUT_PEAK ; 
 int /*<<< orphan*/  MAX34440_MFR_TEMPERATURE_PEAK ; 
 int /*<<< orphan*/  MAX34440_MFR_VOUT_MIN ; 
 int /*<<< orphan*/  MAX34440_MFR_VOUT_PEAK ; 
 int /*<<< orphan*/  MAX34446_MFR_IOUT_AVG ; 
 int /*<<< orphan*/  MAX34446_MFR_POUT_AVG ; 
 int /*<<< orphan*/  MAX34446_MFR_POUT_PEAK ; 
 int /*<<< orphan*/  MAX34446_MFR_TEMPERATURE_AVG ; 
#define  PMBUS_VIRT_READ_IOUT_AVG 139 
#define  PMBUS_VIRT_READ_IOUT_MAX 138 
#define  PMBUS_VIRT_READ_POUT_AVG 137 
#define  PMBUS_VIRT_READ_POUT_MAX 136 
#define  PMBUS_VIRT_READ_TEMP_AVG 135 
#define  PMBUS_VIRT_READ_TEMP_MAX 134 
#define  PMBUS_VIRT_READ_VOUT_MAX 133 
#define  PMBUS_VIRT_READ_VOUT_MIN 132 
#define  PMBUS_VIRT_RESET_IOUT_HISTORY 131 
#define  PMBUS_VIRT_RESET_POUT_HISTORY 130 
#define  PMBUS_VIRT_RESET_TEMP_HISTORY 129 
#define  PMBUS_VIRT_RESET_VOUT_HISTORY 128 
 int /*<<< orphan*/  max34446 ; 
 int /*<<< orphan*/  max34451 ; 
 int /*<<< orphan*/  max34460 ; 
 int /*<<< orphan*/  max34461 ; 
 struct pmbus_driver_info* pmbus_get_driver_info (struct i2c_client*) ; 
 int pmbus_read_word_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 struct max34440_data* to_max34440_data (struct pmbus_driver_info const*) ; 

__attribute__((used)) static int max34440_read_word_data(struct i2c_client *client, int page, int reg)
{
	int ret;
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	const struct max34440_data *data = to_max34440_data(info);

	switch (reg) {
	case PMBUS_VIRT_READ_VOUT_MIN:
		ret = pmbus_read_word_data(client, page,
					   MAX34440_MFR_VOUT_MIN);
		break;
	case PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_read_word_data(client, page,
					   MAX34440_MFR_VOUT_PEAK);
		break;
	case PMBUS_VIRT_READ_IOUT_AVG:
		if (data->id != max34446 && data->id != max34451)
			return -ENXIO;
		ret = pmbus_read_word_data(client, page,
					   MAX34446_MFR_IOUT_AVG);
		break;
	case PMBUS_VIRT_READ_IOUT_MAX:
		ret = pmbus_read_word_data(client, page,
					   MAX34440_MFR_IOUT_PEAK);
		break;
	case PMBUS_VIRT_READ_POUT_AVG:
		if (data->id != max34446)
			return -ENXIO;
		ret = pmbus_read_word_data(client, page,
					   MAX34446_MFR_POUT_AVG);
		break;
	case PMBUS_VIRT_READ_POUT_MAX:
		if (data->id != max34446)
			return -ENXIO;
		ret = pmbus_read_word_data(client, page,
					   MAX34446_MFR_POUT_PEAK);
		break;
	case PMBUS_VIRT_READ_TEMP_AVG:
		if (data->id != max34446 && data->id != max34460 &&
		    data->id != max34461)
			return -ENXIO;
		ret = pmbus_read_word_data(client, page,
					   MAX34446_MFR_TEMPERATURE_AVG);
		break;
	case PMBUS_VIRT_READ_TEMP_MAX:
		ret = pmbus_read_word_data(client, page,
					   MAX34440_MFR_TEMPERATURE_PEAK);
		break;
	case PMBUS_VIRT_RESET_POUT_HISTORY:
		if (data->id != max34446)
			return -ENXIO;
		ret = 0;
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
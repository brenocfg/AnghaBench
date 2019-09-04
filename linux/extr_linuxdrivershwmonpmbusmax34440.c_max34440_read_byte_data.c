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
 int MAX34440_STATUS_OC_FAULT ; 
 int MAX34440_STATUS_OC_WARN ; 
 int MAX34440_STATUS_OT_FAULT ; 
 int MAX34440_STATUS_OT_WARN ; 
 int PB_IOUT_OC_FAULT ; 
 int PB_IOUT_OC_WARNING ; 
 int PB_TEMP_OT_FAULT ; 
 int PB_TEMP_OT_WARNING ; 
#define  PMBUS_STATUS_IOUT 129 
 int /*<<< orphan*/  PMBUS_STATUS_MFR_SPECIFIC ; 
#define  PMBUS_STATUS_TEMPERATURE 128 
 int pmbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmbus_set_page (struct i2c_client*,int) ; 

__attribute__((used)) static int max34440_read_byte_data(struct i2c_client *client, int page, int reg)
{
	int ret = 0;
	int mfg_status;

	if (page >= 0) {
		ret = pmbus_set_page(client, page);
		if (ret < 0)
			return ret;
	}

	switch (reg) {
	case PMBUS_STATUS_IOUT:
		mfg_status = pmbus_read_word_data(client, 0,
						  PMBUS_STATUS_MFR_SPECIFIC);
		if (mfg_status < 0)
			return mfg_status;
		if (mfg_status & MAX34440_STATUS_OC_WARN)
			ret |= PB_IOUT_OC_WARNING;
		if (mfg_status & MAX34440_STATUS_OC_FAULT)
			ret |= PB_IOUT_OC_FAULT;
		break;
	case PMBUS_STATUS_TEMPERATURE:
		mfg_status = pmbus_read_word_data(client, 0,
						  PMBUS_STATUS_MFR_SPECIFIC);
		if (mfg_status < 0)
			return mfg_status;
		if (mfg_status & MAX34440_STATUS_OT_WARN)
			ret |= PB_TEMP_OT_WARNING;
		if (mfg_status & MAX34440_STATUS_OT_FAULT)
			ret |= PB_TEMP_OT_FAULT;
		break;
	default:
		ret = -ENODATA;
		break;
	}
	return ret;
}
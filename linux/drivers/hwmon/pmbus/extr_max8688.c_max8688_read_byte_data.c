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
 int /*<<< orphan*/  MAX8688_MFG_STATUS ; 
 int MAX8688_STATUS_OC_FAULT ; 
 int MAX8688_STATUS_OC_WARNING ; 
 int MAX8688_STATUS_OT_FAULT ; 
 int MAX8688_STATUS_OT_WARNING ; 
 int MAX8688_STATUS_OV_FAULT ; 
 int MAX8688_STATUS_OV_WARNING ; 
 int MAX8688_STATUS_UC_FAULT ; 
 int MAX8688_STATUS_UV_FAULT ; 
 int MAX8688_STATUS_UV_WARNING ; 
 int PB_IOUT_OC_FAULT ; 
 int PB_IOUT_OC_WARNING ; 
 int PB_IOUT_UC_FAULT ; 
 int PB_TEMP_OT_FAULT ; 
 int PB_TEMP_OT_WARNING ; 
 int PB_VOLTAGE_OV_FAULT ; 
 int PB_VOLTAGE_OV_WARNING ; 
 int PB_VOLTAGE_UV_FAULT ; 
 int PB_VOLTAGE_UV_WARNING ; 
#define  PMBUS_STATUS_IOUT 130 
#define  PMBUS_STATUS_TEMPERATURE 129 
#define  PMBUS_STATUS_VOUT 128 
 int pmbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8688_read_byte_data(struct i2c_client *client, int page, int reg)
{
	int ret = 0;
	int mfg_status;

	if (page > 0)
		return -ENXIO;

	switch (reg) {
	case PMBUS_STATUS_VOUT:
		mfg_status = pmbus_read_word_data(client, 0,
						  MAX8688_MFG_STATUS);
		if (mfg_status < 0)
			return mfg_status;
		if (mfg_status & MAX8688_STATUS_UV_WARNING)
			ret |= PB_VOLTAGE_UV_WARNING;
		if (mfg_status & MAX8688_STATUS_UV_FAULT)
			ret |= PB_VOLTAGE_UV_FAULT;
		if (mfg_status & MAX8688_STATUS_OV_WARNING)
			ret |= PB_VOLTAGE_OV_WARNING;
		if (mfg_status & MAX8688_STATUS_OV_FAULT)
			ret |= PB_VOLTAGE_OV_FAULT;
		break;
	case PMBUS_STATUS_IOUT:
		mfg_status = pmbus_read_word_data(client, 0,
						  MAX8688_MFG_STATUS);
		if (mfg_status < 0)
			return mfg_status;
		if (mfg_status & MAX8688_STATUS_UC_FAULT)
			ret |= PB_IOUT_UC_FAULT;
		if (mfg_status & MAX8688_STATUS_OC_WARNING)
			ret |= PB_IOUT_OC_WARNING;
		if (mfg_status & MAX8688_STATUS_OC_FAULT)
			ret |= PB_IOUT_OC_FAULT;
		break;
	case PMBUS_STATUS_TEMPERATURE:
		mfg_status = pmbus_read_word_data(client, 0,
						  MAX8688_MFG_STATUS);
		if (mfg_status < 0)
			return mfg_status;
		if (mfg_status & MAX8688_STATUS_OT_WARNING)
			ret |= PB_TEMP_OT_WARNING;
		if (mfg_status & MAX8688_STATUS_OT_FAULT)
			ret |= PB_TEMP_OT_FAULT;
		break;
	default:
		ret = -ENODATA;
		break;
	}
	return ret;
}
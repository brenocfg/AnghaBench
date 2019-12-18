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
 int CFFPS_MFR_CURRENT_SHARE_WARNING ; 
 int CFFPS_MFR_FAN_FAULT ; 
 int CFFPS_MFR_OC_FAULT ; 
 int CFFPS_MFR_OV_FAULT ; 
 int CFFPS_MFR_THERMAL_FAULT ; 
 int CFFPS_MFR_UV_FAULT ; 
 int CFFPS_MFR_VAUX_FAULT ; 
 int ENODATA ; 
 int PB_CURRENT_SHARE_FAULT ; 
 int PB_FAN_FAN1_FAULT ; 
 int PB_IOUT_OC_FAULT ; 
 int PB_TEMP_OT_FAULT ; 
 int PB_VOLTAGE_OV_FAULT ; 
 int PB_VOLTAGE_UV_FAULT ; 
#define  PMBUS_STATUS_FAN_12 131 
#define  PMBUS_STATUS_IOUT 130 
 int PMBUS_STATUS_MFR_SPECIFIC ; 
#define  PMBUS_STATUS_TEMPERATURE 129 
#define  PMBUS_STATUS_VOUT 128 
 int pmbus_read_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int ibm_cffps_read_byte_data(struct i2c_client *client, int page,
				    int reg)
{
	int rc, mfr;

	switch (reg) {
	case PMBUS_STATUS_VOUT:
	case PMBUS_STATUS_IOUT:
	case PMBUS_STATUS_TEMPERATURE:
	case PMBUS_STATUS_FAN_12:
		rc = pmbus_read_byte_data(client, page, reg);
		if (rc < 0)
			return rc;

		mfr = pmbus_read_byte_data(client, page,
					   PMBUS_STATUS_MFR_SPECIFIC);
		if (mfr < 0)
			/*
			 * Return the status register instead of an error,
			 * since we successfully read status.
			 */
			return rc;

		/* Add MFR_SPECIFIC bits to the standard pmbus status regs. */
		if (reg == PMBUS_STATUS_FAN_12) {
			if (mfr & CFFPS_MFR_FAN_FAULT)
				rc |= PB_FAN_FAN1_FAULT;
		} else if (reg == PMBUS_STATUS_TEMPERATURE) {
			if (mfr & CFFPS_MFR_THERMAL_FAULT)
				rc |= PB_TEMP_OT_FAULT;
		} else if (reg == PMBUS_STATUS_VOUT) {
			if (mfr & (CFFPS_MFR_OV_FAULT | CFFPS_MFR_VAUX_FAULT))
				rc |= PB_VOLTAGE_OV_FAULT;
			if (mfr & CFFPS_MFR_UV_FAULT)
				rc |= PB_VOLTAGE_UV_FAULT;
		} else if (reg == PMBUS_STATUS_IOUT) {
			if (mfr & CFFPS_MFR_OC_FAULT)
				rc |= PB_IOUT_OC_FAULT;
			if (mfr & CFFPS_MFR_CURRENT_SHARE_WARNING)
				rc |= PB_CURRENT_SHARE_FAULT;
		}
		break;
	default:
		rc = -ENODATA;
		break;
	}

	return rc;
}
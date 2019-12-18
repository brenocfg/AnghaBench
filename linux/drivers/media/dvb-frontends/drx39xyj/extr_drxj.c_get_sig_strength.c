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
typedef  int u16 ;
struct i2c_device_addr {int dummy; } ;
struct drx_demod_instance {struct i2c_device_addr* my_i2c_dev_addr; } ;

/* Variables and functions */
 int DRXJ_AGC_SNS ; 
 int DRXJ_AGC_TOP ; 
 int DRXJ_RFAGC_MAX ; 
 int DRXJ_RFAGC_MIN ; 
 int EIO ; 
 int /*<<< orphan*/  IQM_AF_AGC_IF__A ; 
 int IQM_AF_AGC_IF__M ; 
 int /*<<< orphan*/  IQM_AF_AGC_RF__A ; 
 int IQM_AF_AGC_RF__M ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int get_sig_strength(struct drx_demod_instance *demod, u16 *sig_strength)
{
	struct i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	int rc;
	u16 rf_gain = 0;
	u16 if_gain = 0;
	u16 if_agc_sns = 0;
	u16 if_agc_top = 0;
	u16 rf_agc_max = 0;
	u16 rf_agc_min = 0;

	rc = drxj_dap_read_reg16(dev_addr, IQM_AF_AGC_IF__A, &if_gain, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	if_gain &= IQM_AF_AGC_IF__M;
	rc = drxj_dap_read_reg16(dev_addr, IQM_AF_AGC_RF__A, &rf_gain, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rf_gain &= IQM_AF_AGC_RF__M;

	if_agc_sns = DRXJ_AGC_SNS;
	if_agc_top = DRXJ_AGC_TOP;
	rf_agc_max = DRXJ_RFAGC_MAX;
	rf_agc_min = DRXJ_RFAGC_MIN;

	if (if_gain > if_agc_top) {
		if (rf_gain > rf_agc_max)
			*sig_strength = 100;
		else if (rf_gain > rf_agc_min) {
			if (rf_agc_max == rf_agc_min) {
				pr_err("error: rf_agc_max == rf_agc_min\n");
				return -EIO;
			}
			*sig_strength =
			75 + 25 * (rf_gain - rf_agc_min) / (rf_agc_max -
								rf_agc_min);
		} else
			*sig_strength = 75;
	} else if (if_gain > if_agc_sns) {
		if (if_agc_top == if_agc_sns) {
			pr_err("error: if_agc_top == if_agc_sns\n");
			return -EIO;
		}
		*sig_strength =
		20 + 55 * (if_gain - if_agc_sns) / (if_agc_top - if_agc_sns);
	} else {
		if (!if_agc_sns) {
			pr_err("error: if_agc_sns is zero!\n");
			return -EIO;
		}
		*sig_strength = (20 * if_gain / if_agc_sns);
	}

	if (*sig_strength <= 7)
		*sig_strength = 0;

	return 0;
rw_error:
	return rc;
}
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
typedef  int u32 ;
typedef  int u16 ;
struct i2c_device_addr {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int FEC_RS_MEASUREMENT_PERIOD ; 
 int FEC_RS_MEASUREMENT_PRESCALE ; 
 int FEC_RS_NR_BIT_ERRORS_EXP__B ; 
 int FEC_RS_NR_BIT_ERRORS_EXP__M ; 
 int FEC_RS_NR_BIT_ERRORS_FIXED_MANT__M ; 
 int /*<<< orphan*/  FEC_RS_NR_BIT_ERRORS__A ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int get_vs_bpost_viterbi_ber(struct i2c_device_addr *dev_addr,
				    u32 *ber, u32 *cnt)
{
	int rc;
	u16 data = 0;
	u16 period = 0;
	u16 prescale = 0;
	u16 bit_errors_mant = 0;
	u16 bit_errors_exp = 0;

	rc = drxj_dap_read_reg16(dev_addr, FEC_RS_NR_BIT_ERRORS__A, &data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	period = FEC_RS_MEASUREMENT_PERIOD;
	prescale = FEC_RS_MEASUREMENT_PRESCALE;

	bit_errors_mant = data & FEC_RS_NR_BIT_ERRORS_FIXED_MANT__M;
	bit_errors_exp = (data & FEC_RS_NR_BIT_ERRORS_EXP__M)
	    >> FEC_RS_NR_BIT_ERRORS_EXP__B;

	*cnt = period * prescale * 207 * ((bit_errors_exp > 2) ? 1 : 8);

	if (((bit_errors_mant << bit_errors_exp) >> 3) > 68700)
		*ber = (*cnt) * 26570;
	else {
		if (period * prescale == 0) {
			pr_err("error: period and/or prescale is zero!\n");
			return -EIO;
		}
		*ber = bit_errors_mant << ((bit_errors_exp > 2) ?
			(bit_errors_exp - 3) : bit_errors_exp);
	}

	return 0;
rw_error:
	return rc;
}
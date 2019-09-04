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

/* Variables and functions */
 int /*<<< orphan*/  VSB_TOP_ERR_ENERGY_H__A ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ log1_times100 (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int get_vsbmer(struct i2c_device_addr *dev_addr, u16 *mer)
{
	int rc;
	u16 data_hi = 0;

	rc = drxj_dap_read_reg16(dev_addr, VSB_TOP_ERR_ENERGY_H__A, &data_hi, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	*mer =
	    (u16) (log1_times100(21504) - log1_times100((data_hi << 6) / 52));

	return 0;
rw_error:
	return rc;
}
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
typedef  int u8 ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PB_I2C_BUSY ; 
 int /*<<< orphan*/  TWL4030_PM_MASTER_PB_CFG ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_wait_pb_ready(void)
{

	int	ret;
	int	timeout = 10;
	u8	val;

	do {
		ret = twl_i2c_read_u8(TWL_MODULE_PM_MASTER, &val,
				      TWL4030_PM_MASTER_PB_CFG);
		if (ret < 0)
			return ret;

		if (!(val & PB_I2C_BUSY))
			return 0;

		mdelay(1);
		timeout--;
	} while (timeout);

	return -ETIMEDOUT;
}
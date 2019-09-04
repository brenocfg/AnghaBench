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
struct twl4030_madc_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int TWL4030_MADC_BUSY ; 
 int TWL4030_MADC_EOC_SW ; 
 int /*<<< orphan*/  TWL4030_MODULE_MADC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int twl4030_madc_wait_conversion_ready(struct twl4030_madc_data *madc,
					      unsigned int timeout_ms,
					      u8 status_reg)
{
	unsigned long timeout;
	int ret;

	timeout = jiffies + msecs_to_jiffies(timeout_ms);
	do {
		u8 reg;

		ret = twl_i2c_read_u8(TWL4030_MODULE_MADC, &reg, status_reg);
		if (ret) {
			dev_err(madc->dev,
				"unable to read status register 0x%X\n",
				status_reg);
			return ret;
		}
		if (!(reg & TWL4030_MADC_BUSY) && (reg & TWL4030_MADC_EOC_SW))
			return 0;
		usleep_range(500, 2000);
	} while (!time_after(jiffies, timeout));
	dev_err(madc->dev, "conversion timeout!\n");

	return -EAGAIN;
}
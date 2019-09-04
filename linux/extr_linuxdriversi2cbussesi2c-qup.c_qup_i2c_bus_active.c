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
struct qup_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int I2C_STATUS_BUS_ACTIVE ; 
 scalar_t__ QUP_I2C_STATUS ; 
 int jiffies ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_after (int,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int qup_i2c_bus_active(struct qup_i2c_dev *qup, int len)
{
	unsigned long timeout;
	u32 status;
	int ret = 0;

	timeout = jiffies + len * 4;
	for (;;) {
		status = readl(qup->base + QUP_I2C_STATUS);
		if (!(status & I2C_STATUS_BUS_ACTIVE))
			break;

		if (time_after(jiffies, timeout))
			ret = -ETIMEDOUT;

		usleep_range(len, len * 2);
	}

	return ret;
}
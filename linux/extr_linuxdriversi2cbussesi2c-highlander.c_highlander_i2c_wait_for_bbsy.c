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
struct highlander_i2c_dev {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ SMCR ; 
 int SMCR_BBSY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iic_timeout ; 
 int ioread16 (scalar_t__) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int highlander_i2c_wait_for_bbsy(struct highlander_i2c_dev *dev)
{
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(iic_timeout);
	while (ioread16(dev->base + SMCR) & SMCR_BBSY) {
		if (time_after(jiffies, timeout)) {
			dev_warn(dev->dev, "timeout waiting for bus ready\n");
			return -ETIMEDOUT;
		}

		msleep(1);
	}

	return 0;
}
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
struct bcm_kona_i2c_dev {int /*<<< orphan*/  device; scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int ISR_CMDBUSY_MASK ; 
 scalar_t__ ISR_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int bcm_kona_i2c_wait_if_busy(struct bcm_kona_i2c_dev *dev)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(I2C_TIMEOUT);

	while (readl(dev->base + ISR_OFFSET) & ISR_CMDBUSY_MASK)
		if (time_after(jiffies, timeout)) {
			dev_err(dev->device, "CMDBUSY timeout\n");
			return -ETIMEDOUT;
		}

	return 0;
}
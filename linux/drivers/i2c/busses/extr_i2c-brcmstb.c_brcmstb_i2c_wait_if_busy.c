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
struct brcmstb_i2c_dev {int dummy; } ;

/* Variables and functions */
 int BSC_IIC_EN_INTRP_MASK ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int bsc_readl (struct brcmstb_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  iic_enable ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int brcmstb_i2c_wait_if_busy(struct brcmstb_i2c_dev *dev)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(I2C_TIMEOUT);

	while ((bsc_readl(dev, iic_enable) & BSC_IIC_EN_INTRP_MASK)) {
		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;
		cpu_relax();
	}
	return 0;
}
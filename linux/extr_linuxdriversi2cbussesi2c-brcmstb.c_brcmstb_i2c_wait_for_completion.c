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
struct brcmstb_i2c_dev {scalar_t__ irq; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int BSC_IIC_EN_INTRP_MASK ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int /*<<< orphan*/  INT_DISABLE ; 
 int /*<<< orphan*/  brcmstb_i2c_enable_disable_irq (struct brcmstb_i2c_dev*,int /*<<< orphan*/ ) ; 
 int bsc_readl (struct brcmstb_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  iic_enable ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int brcmstb_i2c_wait_for_completion(struct brcmstb_i2c_dev *dev)
{
	int ret = 0;
	unsigned long timeout = msecs_to_jiffies(I2C_TIMEOUT);

	if (dev->irq >= 0) {
		if (!wait_for_completion_timeout(&dev->done, timeout))
			ret = -ETIMEDOUT;
	} else {
		/* we are in polling mode */
		u32 bsc_intrp;
		unsigned long time_left = jiffies + timeout;

		do {
			bsc_intrp = bsc_readl(dev, iic_enable) &
				BSC_IIC_EN_INTRP_MASK;
			if (time_after(jiffies, time_left)) {
				ret = -ETIMEDOUT;
				break;
			}
			cpu_relax();
		} while (!bsc_intrp);
	}

	if (dev->irq < 0 || ret == -ETIMEDOUT)
		brcmstb_i2c_enable_disable_irq(dev, INT_DISABLE);

	return ret;
}
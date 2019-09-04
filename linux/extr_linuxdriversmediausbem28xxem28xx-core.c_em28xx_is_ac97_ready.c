#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct em28xx {TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EM28XX_AC97_XFER_TIMEOUT ; 
 int /*<<< orphan*/  EM28XX_R43_AC97BUSY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int em28xx_read_reg (struct em28xx*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 

__attribute__((used)) static int em28xx_is_ac97_ready(struct em28xx *dev)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(EM28XX_AC97_XFER_TIMEOUT);
	int ret;

	/* Wait up to 50 ms for AC97 command to complete */
	while (time_is_after_jiffies(timeout)) {
		ret = em28xx_read_reg(dev, EM28XX_R43_AC97BUSY);
		if (ret < 0)
			return ret;

		if (!(ret & 0x01))
			return 0;
		msleep(5);
	}

	dev_warn(&dev->intf->dev,
		 "AC97 command still being executed: not handled properly!\n");
	return -EBUSY;
}
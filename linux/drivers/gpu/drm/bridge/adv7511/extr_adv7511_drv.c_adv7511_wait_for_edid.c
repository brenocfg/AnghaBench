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
struct adv7511 {scalar_t__ edid_read; int /*<<< orphan*/  wq; TYPE_1__* i2c_main; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int EIO ; 
 int adv7511_irq_process (struct adv7511*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7511_wait_for_edid(struct adv7511 *adv7511, int timeout)
{
	int ret;

	if (adv7511->i2c_main->irq) {
		ret = wait_event_interruptible_timeout(adv7511->wq,
				adv7511->edid_read, msecs_to_jiffies(timeout));
	} else {
		for (; timeout > 0; timeout -= 25) {
			ret = adv7511_irq_process(adv7511, false);
			if (ret < 0)
				break;

			if (adv7511->edid_read)
				break;

			msleep(25);
		}
	}

	return adv7511->edid_read ? 0 : -EIO;
}
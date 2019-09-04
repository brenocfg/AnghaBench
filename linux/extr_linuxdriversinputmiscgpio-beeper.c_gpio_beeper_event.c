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
struct input_dev {int dummy; } ;
struct gpio_beeper {int beeping; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 unsigned int EV_SND ; 
 unsigned int SND_BELL ; 
 struct gpio_beeper* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_beeper_event(struct input_dev *dev, unsigned int type,
			     unsigned int code, int value)
{
	struct gpio_beeper *beep = input_get_drvdata(dev);

	if (type != EV_SND || code != SND_BELL)
		return -ENOTSUPP;

	if (value < 0)
		return -EINVAL;

	beep->beeping = value;
	/* Schedule work to actually turn the beeper on or off */
	schedule_work(&beep->work);

	return 0;
}
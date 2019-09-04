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
struct max7301 {int /*<<< orphan*/  lock; int /*<<< orphan*/  chip; int /*<<< orphan*/  (* write ) (struct device*,int,int) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct max7301* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct device*,int,int) ; 

int __max730x_remove(struct device *dev)
{
	struct max7301 *ts = dev_get_drvdata(dev);

	if (ts == NULL)
		return -ENODEV;

	/* Power down the chip and disable IRQ output */
	ts->write(dev, 0x04, 0x00);
	gpiochip_remove(&ts->chip);
	mutex_destroy(&ts->lock);
	return 0;
}
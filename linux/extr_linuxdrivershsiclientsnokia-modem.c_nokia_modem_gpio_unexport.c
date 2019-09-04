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
struct nokia_modem_device {int gpio_amount; TYPE_1__* gpios; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct nokia_modem_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpiod_unexport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nokia_modem_gpio_unexport(struct device *dev)
{
	struct nokia_modem_device *modem = dev_get_drvdata(dev);
	int i;

	for (i = 0; i < modem->gpio_amount; i++) {
		sysfs_remove_link(&dev->kobj, modem->gpios[i].name);
		gpiod_unexport(modem->gpios[i].gpio);
	}
}
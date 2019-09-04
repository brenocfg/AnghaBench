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
struct gpio_device {struct gpio_device* descs; int /*<<< orphan*/  label; int /*<<< orphan*/  id; int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct gpio_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpio_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gpio_device*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gpiodevice_release(struct device *dev)
{
	struct gpio_device *gdev = dev_get_drvdata(dev);

	list_del(&gdev->list);
	ida_simple_remove(&gpio_ida, gdev->id);
	kfree_const(gdev->label);
	kfree(gdev->descs);
	kfree(gdev);
}
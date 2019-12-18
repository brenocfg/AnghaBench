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
typedef  int /*<<< orphan*/  umode_t ;
struct usb_class_driver {char* (* devnode ) (struct device*,int /*<<< orphan*/ *) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 struct usb_class_driver* dev_get_drvdata (struct device*) ; 
 char* stub1 (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *usb_devnode(struct device *dev, umode_t *mode)
{
	struct usb_class_driver *drv;

	drv = dev_get_drvdata(dev);
	if (!drv || !drv->devnode)
		return NULL;
	return drv->devnode(dev, mode);
}
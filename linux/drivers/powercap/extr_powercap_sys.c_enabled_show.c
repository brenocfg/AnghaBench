#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct powercap_zone {TYPE_2__* ops; } ;
struct powercap_control_type {TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {scalar_t__ parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {scalar_t__ (* get_enable ) (struct powercap_zone*,int*) ;} ;
struct TYPE_3__ {scalar_t__ (* get_enable ) (struct powercap_control_type*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ stub1 (struct powercap_zone*,int*) ; 
 scalar_t__ stub2 (struct powercap_control_type*,int*) ; 
 struct powercap_control_type* to_powercap_control_type (struct device*) ; 
 struct powercap_zone* to_powercap_zone (struct device*) ; 

__attribute__((used)) static ssize_t enabled_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	bool mode = true;

	/* Default is enabled */
	if (dev->parent) {
		struct powercap_zone *power_zone = to_powercap_zone(dev);
		if (power_zone->ops->get_enable)
			if (power_zone->ops->get_enable(power_zone, &mode))
				mode = false;
	} else {
		struct powercap_control_type *control_type =
						to_powercap_control_type(dev);
		if (control_type->ops && control_type->ops->get_enable)
			if (control_type->ops->get_enable(control_type, &mode))
				mode = false;
	}

	return sprintf(buf, "%d\n", mode);
}
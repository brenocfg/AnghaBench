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
typedef  int /*<<< orphan*/  umode_t ;
struct most_channel {TYPE_2__* iface; } ;
struct kobject {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {scalar_t__ interface; } ;

/* Variables and functions */
 scalar_t__ ITYPE_MEDIALB_DIM2 ; 
 scalar_t__ ITYPE_USB ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 struct most_channel* to_channel (struct device*) ; 
 struct device_attribute* to_dev_attr (struct attribute*) ; 

__attribute__((used)) static umode_t channel_attr_is_visible(struct kobject *kobj,
				       struct attribute *attr, int index)
{
	struct device_attribute *dev_attr = to_dev_attr(attr);
	struct device *dev = kobj_to_dev(kobj);
	struct most_channel *c = to_channel(dev);

	if (!strcmp(dev_attr->attr.name, "set_dbr_size") &&
	    (c->iface->interface != ITYPE_MEDIALB_DIM2))
		return 0;
	if (!strcmp(dev_attr->attr.name, "set_packets_per_xact") &&
	    (c->iface->interface != ITYPE_USB))
		return 0;

	return attr->mode;
}
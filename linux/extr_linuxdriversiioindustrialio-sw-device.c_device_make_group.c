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
struct TYPE_2__ {int /*<<< orphan*/  ci_name; } ;
struct config_group {TYPE_1__ cg_item; } ;
struct iio_sw_device {struct config_group group; } ;

/* Variables and functions */
 struct config_group* ERR_CAST (struct iio_sw_device*) ; 
 scalar_t__ IS_ERR (struct iio_sw_device*) ; 
 int /*<<< orphan*/  config_item_set_name (TYPE_1__*,char*,char const*) ; 
 struct iio_sw_device* iio_sw_device_create (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct config_group *device_make_group(struct config_group *group,
					      const char *name)
{
	struct iio_sw_device *d;

	d = iio_sw_device_create(group->cg_item.ci_name, name);
	if (IS_ERR(d))
		return ERR_CAST(d);

	config_item_set_name(&d->group.cg_item, "%s", name);

	return &d->group;
}
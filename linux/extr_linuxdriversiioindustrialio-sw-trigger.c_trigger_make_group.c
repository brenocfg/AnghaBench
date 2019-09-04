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
struct iio_sw_trigger {struct config_group group; } ;

/* Variables and functions */
 struct config_group* ERR_CAST (struct iio_sw_trigger*) ; 
 scalar_t__ IS_ERR (struct iio_sw_trigger*) ; 
 int /*<<< orphan*/  config_item_set_name (TYPE_1__*,char*,char const*) ; 
 struct iio_sw_trigger* iio_sw_trigger_create (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct config_group *trigger_make_group(struct config_group *group,
					       const char *name)
{
	struct iio_sw_trigger *t;

	t = iio_sw_trigger_create(group->cg_item.ci_name, name);
	if (IS_ERR(t))
		return ERR_CAST(t);

	config_item_set_name(&t->group.cg_item, "%s", name);

	return &t->group;
}
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
struct iio_sw_trigger_type {int /*<<< orphan*/  group; int /*<<< orphan*/  name; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct iio_sw_trigger_type* __iio_find_sw_trigger_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configfs_register_default_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_trigger_type_group_type ; 
 int /*<<< orphan*/  iio_trigger_types_list ; 
 int /*<<< orphan*/  iio_trigger_types_lock ; 
 int /*<<< orphan*/  iio_triggers_group ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int iio_register_sw_trigger_type(struct iio_sw_trigger_type *t)
{
	struct iio_sw_trigger_type *iter;
	int ret = 0;

	mutex_lock(&iio_trigger_types_lock);
	iter = __iio_find_sw_trigger_type(t->name, strlen(t->name));
	if (iter)
		ret = -EBUSY;
	else
		list_add_tail(&t->list, &iio_trigger_types_list);
	mutex_unlock(&iio_trigger_types_lock);

	if (ret)
		return ret;

	t->group = configfs_register_default_group(iio_triggers_group, t->name,
						&iio_trigger_type_group_type);
	if (IS_ERR(t->group))
		ret = PTR_ERR(t->group);

	return ret;
}
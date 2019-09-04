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
struct iio_sw_trigger_type {int /*<<< orphan*/  group; int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct iio_sw_trigger_type* __iio_find_sw_trigger_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configfs_unregister_default_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_types_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void iio_unregister_sw_trigger_type(struct iio_sw_trigger_type *t)
{
	struct iio_sw_trigger_type *iter;

	mutex_lock(&iio_trigger_types_lock);
	iter = __iio_find_sw_trigger_type(t->name, strlen(t->name));
	if (iter)
		list_del(&t->list);
	mutex_unlock(&iio_trigger_types_lock);

	configfs_unregister_default_group(t->group);
}
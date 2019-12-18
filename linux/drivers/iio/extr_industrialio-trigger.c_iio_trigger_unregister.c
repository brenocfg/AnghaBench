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
struct iio_trigger {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_ida ; 
 int /*<<< orphan*/  iio_trigger_list_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void iio_trigger_unregister(struct iio_trigger *trig_info)
{
	mutex_lock(&iio_trigger_list_lock);
	list_del(&trig_info->list);
	mutex_unlock(&iio_trigger_list_lock);

	ida_simple_remove(&iio_trigger_ida, trig_info->id);
	/* Possible issue in here */
	device_del(&trig_info->dev);
}
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
struct device {int dummy; } ;
struct adt7475_data {int valid; int /*<<< orphan*/  lock; scalar_t__ measure_updated; } ;

/* Variables and functions */
 struct adt7475_data* ERR_PTR (int) ; 
 int HZ ; 
 int adt7475_update_measure (struct device*) ; 
 struct adt7475_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct adt7475_data *adt7475_update_device(struct device *dev)
{
	struct adt7475_data *data = dev_get_drvdata(dev);
	int ret;

	mutex_lock(&data->lock);

	/* Measurement values update every 2 seconds */
	if (time_after(jiffies, data->measure_updated + HZ * 2) ||
	    !data->valid) {
		ret = adt7475_update_measure(dev);
		if (ret) {
			data->valid = false;
			mutex_unlock(&data->lock);
			return ERR_PTR(ret);
		}
		data->measure_updated = jiffies;
		data->valid = true;
	}

	mutex_unlock(&data->lock);

	return data;
}
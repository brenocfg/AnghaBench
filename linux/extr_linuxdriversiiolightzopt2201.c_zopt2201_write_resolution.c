#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zopt2201_data {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int us; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* zopt2201_resolution ; 
 int zopt2201_set_resolution (struct zopt2201_data*,int) ; 

__attribute__((used)) static int zopt2201_write_resolution(struct zopt2201_data *data,
				     int val, int val2)
{
	int i, ret;

	if (val != 0)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(zopt2201_resolution); i++)
		if (val2 == zopt2201_resolution[i].us) {
			mutex_lock(&data->lock);
			ret = zopt2201_set_resolution(data, i);
			mutex_unlock(&data->lock);
			return ret;
		}

	return -EINVAL;
}
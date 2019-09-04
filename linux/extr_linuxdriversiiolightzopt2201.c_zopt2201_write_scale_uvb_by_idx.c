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
struct zopt2201_data {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  gain; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* zopt2201_scale_als ; 
 int zopt2201_set_gain (struct zopt2201_data*,int /*<<< orphan*/ ) ; 
 int zopt2201_set_resolution (struct zopt2201_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zopt2201_write_scale_uvb_by_idx(struct zopt2201_data *data, int idx)
{
	int ret;

	mutex_lock(&data->lock);
	ret = zopt2201_set_resolution(data, zopt2201_scale_als[idx].res);
	if (ret < 0)
		goto unlock;

	ret = zopt2201_set_gain(data, zopt2201_scale_als[idx].gain);

unlock:
	mutex_unlock(&data->lock);
	return ret;
}
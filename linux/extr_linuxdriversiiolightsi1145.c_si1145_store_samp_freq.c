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
struct si1145_data {int meas_rate; int /*<<< orphan*/  lock; TYPE_1__* part_info; scalar_t__ autonomous; } ;
struct TYPE_2__ {scalar_t__ uncompressed_meas_rate; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si1145_compress (int) ; 
 int si1145_set_meas_rate (struct si1145_data*,int) ; 

__attribute__((used)) static int si1145_store_samp_freq(struct si1145_data *data, int val)
{
	int ret = 0;
	int meas_rate;

	if (val <= 0 || val > 32000)
		return -ERANGE;
	meas_rate = 32000 / val;

	mutex_lock(&data->lock);
	if (data->autonomous) {
		ret = si1145_set_meas_rate(data, meas_rate);
		if (ret)
			goto out;
	}
	if (data->part_info->uncompressed_meas_rate)
		data->meas_rate = meas_rate;
	else
		data->meas_rate = si1145_compress(meas_rate);

out:
	mutex_unlock(&data->lock);

	return ret;
}
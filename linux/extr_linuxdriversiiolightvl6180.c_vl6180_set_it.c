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
struct vl6180_data {int als_it_ms; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VL6180_ALS_IT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vl6180_hold (struct vl6180_data*,int) ; 
 int vl6180_write_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vl6180_set_it(struct vl6180_data *data, int val, int val2)
{
	int ret, it_ms;

	it_ms = (val2 + 500) / 1000; /* round to ms */
	if (val != 0 || it_ms < 1 || it_ms > 512)
		return -EINVAL;

	mutex_lock(&data->lock);
	ret = vl6180_hold(data, true);
	if (ret < 0)
		goto fail;

	ret = vl6180_write_word(data->client, VL6180_ALS_IT, it_ms - 1);

	if (ret >= 0)
		data->als_it_ms = it_ms;

fail:
	vl6180_hold(data, false);
	mutex_unlock(&data->lock);

	return ret;
}
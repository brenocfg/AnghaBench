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
struct apds9960_data {int gesture_mode_running; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  indio_dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS9960_REG_GFIFO_BASE ; 
 scalar_t__ apds9660_fifo_is_empty (struct apds9960_data*) ; 
 int /*<<< orphan*/  iio_push_to_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void apds9960_read_gesture_fifo(struct apds9960_data *data)
{
	int ret, cnt = 0;

	mutex_lock(&data->lock);
	data->gesture_mode_running = 1;

	while (cnt || (cnt = apds9660_fifo_is_empty(data) > 0)) {
		ret = regmap_bulk_read(data->regmap, APDS9960_REG_GFIFO_BASE,
				      &data->buffer, 4);

		if (ret)
			goto err_read;

		iio_push_to_buffers(data->indio_dev, data->buffer);
		cnt--;
	}

err_read:
	data->gesture_mode_running = 0;
	mutex_unlock(&data->lock);
}
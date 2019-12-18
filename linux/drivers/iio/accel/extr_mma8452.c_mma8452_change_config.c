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
typedef  int /*<<< orphan*/  u8 ;
struct mma8452_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mma8452_active (struct mma8452_data*) ; 
 int mma8452_is_active (struct mma8452_data*) ; 
 int mma8452_standby (struct mma8452_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma8452_change_config(struct mma8452_data *data, u8 reg, u8 val)
{
	int ret;
	int is_active;

	mutex_lock(&data->lock);

	is_active = mma8452_is_active(data);
	if (is_active < 0) {
		ret = is_active;
		goto fail;
	}

	/* config can only be changed when in standby */
	if (is_active > 0) {
		ret = mma8452_standby(data);
		if (ret < 0)
			goto fail;
	}

	ret = i2c_smbus_write_byte_data(data->client, reg, val);
	if (ret < 0)
		goto fail;

	if (is_active > 0) {
		ret = mma8452_active(data);
		if (ret < 0)
			goto fail;
	}

	ret = 0;
fail:
	mutex_unlock(&data->lock);

	return ret;
}
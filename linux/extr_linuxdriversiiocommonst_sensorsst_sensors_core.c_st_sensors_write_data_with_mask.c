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
typedef  int u8 ;
struct st_sensor_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  tb; TYPE_1__* tf; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int (* read_byte ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ;int (* write_byte ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int __ffs (int) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

int st_sensors_write_data_with_mask(struct iio_dev *indio_dev,
				    u8 reg_addr, u8 mask, u8 data)
{
	int err;
	u8 new_data;
	struct st_sensor_data *sdata = iio_priv(indio_dev);

	err = sdata->tf->read_byte(&sdata->tb, sdata->dev, reg_addr, &new_data);
	if (err < 0)
		goto st_sensors_write_data_with_mask_error;

	new_data = ((new_data & (~mask)) | ((data << __ffs(mask)) & mask));
	err = sdata->tf->write_byte(&sdata->tb, sdata->dev, reg_addr, new_data);

st_sensors_write_data_with_mask_error:
	return err;
}
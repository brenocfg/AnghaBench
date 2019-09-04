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
typedef  scalar_t__ u8 ;
struct st_sensor_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  tb; TYPE_1__* tf; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int (* write_byte ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;int (* read_byte ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ;} ;

/* Variables and functions */
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

int st_sensors_debugfs_reg_access(struct iio_dev *indio_dev,
				  unsigned reg, unsigned writeval,
				  unsigned *readval)
{
	struct st_sensor_data *sdata = iio_priv(indio_dev);
	u8 readdata;
	int err;

	if (!readval)
		return sdata->tf->write_byte(&sdata->tb, sdata->dev,
					     (u8)reg, (u8)writeval);

	err = sdata->tf->read_byte(&sdata->tb, sdata->dev, (u8)reg, &readdata);
	if (err < 0)
		return err;

	*readval = (unsigned)readdata;

	return 0;
}
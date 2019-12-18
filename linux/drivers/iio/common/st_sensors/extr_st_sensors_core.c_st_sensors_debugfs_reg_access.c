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
struct st_sensor_data {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int st_sensors_debugfs_reg_access(struct iio_dev *indio_dev,
				  unsigned reg, unsigned writeval,
				  unsigned *readval)
{
	struct st_sensor_data *sdata = iio_priv(indio_dev);
	int err;

	if (!readval)
		return regmap_write(sdata->regmap, reg, writeval);

	err = regmap_read(sdata->regmap, reg, readval);
	if (err < 0)
		return err;

	return 0;
}
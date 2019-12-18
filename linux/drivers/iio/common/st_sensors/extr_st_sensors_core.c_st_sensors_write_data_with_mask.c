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
typedef  int u8 ;
struct st_sensor_data {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int __ffs (int) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

int st_sensors_write_data_with_mask(struct iio_dev *indio_dev,
				    u8 reg_addr, u8 mask, u8 data)
{
	struct st_sensor_data *sdata = iio_priv(indio_dev);

	return regmap_update_bits(sdata->regmap,
				  reg_addr, mask, data << __ffs(mask));
}
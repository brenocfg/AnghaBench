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
struct itg3200 {int /*<<< orphan*/  i2c; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int) ; 
 struct itg3200* iio_priv (struct iio_dev*) ; 

int itg3200_write_reg_8(struct iio_dev *indio_dev,
		u8 reg_address, u8 val)
{
	struct itg3200 *st = iio_priv(indio_dev);

	return i2c_smbus_write_byte_data(st->i2c, 0x80 | reg_address, val);
}
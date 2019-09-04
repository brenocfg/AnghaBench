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
typedef  int /*<<< orphan*/  u16 ;
struct us5182d_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int IIO_EV_DIR_FALLING ; 
 int IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  US5182D_REG_PXH_TH ; 
 int /*<<< orphan*/  US5182D_REG_PXL_TH ; 
 int i2c_smbus_write_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int us5182d_setup_prox(struct iio_dev *indio_dev,
			      enum iio_event_direction dir, u16 val)
{
	struct us5182d_data *data = iio_priv(indio_dev);

	if (dir == IIO_EV_DIR_FALLING)
		return i2c_smbus_write_word_data(data->client,
						 US5182D_REG_PXL_TH, val);
	else if (dir == IIO_EV_DIR_RISING)
		return i2c_smbus_write_word_data(data->client,
						 US5182D_REG_PXH_TH, val);

	return 0;
}
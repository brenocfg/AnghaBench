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
struct us5182d_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  US5182D_REG_CFG3 ; 
 int /*<<< orphan*/  US5182D_RESET_CHIP ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int us5182d_reset(struct iio_dev *indio_dev)
{
	struct us5182d_data *data = iio_priv(indio_dev);

	return i2c_smbus_write_byte_data(data->client, US5182D_REG_CFG3,
					 US5182D_RESET_CHIP);
}
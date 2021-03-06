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
struct isl29125_data {int /*<<< orphan*/  conf1; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISL29125_CONF1 ; 
 int /*<<< orphan*/  ISL29125_MODE_RGB ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isl29125_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int isl29125_buffer_preenable(struct iio_dev *indio_dev)
{
	struct isl29125_data *data = iio_priv(indio_dev);

	data->conf1 |= ISL29125_MODE_RGB;
	return i2c_smbus_write_byte_data(data->client, ISL29125_CONF1,
		data->conf1);
}
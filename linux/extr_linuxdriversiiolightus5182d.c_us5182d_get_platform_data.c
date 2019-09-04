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
struct us5182d_data {TYPE_1__* client; int /*<<< orphan*/  default_continuous; int /*<<< orphan*/  lower_dark_gain; int /*<<< orphan*/  upper_dark_gain; int /*<<< orphan*/  us5182d_dark_ths; int /*<<< orphan*/  ga; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  US5182D_GA_RESOLUTION ; 
 int /*<<< orphan*/  US5182D_REG_AUTO_HDARK_GAIN_DEFAULT ; 
 int /*<<< orphan*/  US5182D_REG_AUTO_LDARK_GAIN_DEFAULT ; 
 int /*<<< orphan*/  device_property_read_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_property_read_u16_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_property_read_u32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ device_property_read_u8 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  us5182d_dark_ths_vals ; 

__attribute__((used)) static void us5182d_get_platform_data(struct iio_dev *indio_dev)
{
	struct us5182d_data *data = iio_priv(indio_dev);

	if (device_property_read_u32(&data->client->dev, "upisemi,glass-coef",
				     &data->ga))
		data->ga = US5182D_GA_RESOLUTION;
	if (device_property_read_u16_array(&data->client->dev,
					   "upisemi,dark-ths",
					   data->us5182d_dark_ths,
					   ARRAY_SIZE(us5182d_dark_ths_vals)))
		data->us5182d_dark_ths = us5182d_dark_ths_vals;
	if (device_property_read_u8(&data->client->dev,
				    "upisemi,upper-dark-gain",
				    &data->upper_dark_gain))
		data->upper_dark_gain = US5182D_REG_AUTO_HDARK_GAIN_DEFAULT;
	if (device_property_read_u8(&data->client->dev,
				    "upisemi,lower-dark-gain",
				    &data->lower_dark_gain))
		data->lower_dark_gain = US5182D_REG_AUTO_LDARK_GAIN_DEFAULT;
	data->default_continuous = device_property_read_bool(&data->client->dev,
							     "upisemi,continuous");
}
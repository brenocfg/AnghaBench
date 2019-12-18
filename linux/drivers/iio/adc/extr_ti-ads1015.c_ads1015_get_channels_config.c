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
struct iio_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ads1015_platform_data {int /*<<< orphan*/  channel_data; } ;
struct ads1015_data {TYPE_1__* channel_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_rate; int /*<<< orphan*/  pga; } ;

/* Variables and functions */
 unsigned int ADS1015_CHANNELS ; 
 int /*<<< orphan*/  ADS1015_DEFAULT_DATA_RATE ; 
 int /*<<< orphan*/  ADS1015_DEFAULT_PGA ; 
 int /*<<< orphan*/  ads1015_get_channels_config_of (struct i2c_client*) ; 
 struct ads1015_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 struct ads1015_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ads1015_get_channels_config(struct i2c_client *client)
{
	unsigned int k;

	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct ads1015_data *data = iio_priv(indio_dev);
	struct ads1015_platform_data *pdata = dev_get_platdata(&client->dev);

	/* prefer platform data */
	if (pdata) {
		memcpy(data->channel_data, pdata->channel_data,
		       sizeof(data->channel_data));
		return;
	}

#ifdef CONFIG_OF
	if (!ads1015_get_channels_config_of(client))
		return;
#endif
	/* fallback on default configuration */
	for (k = 0; k < ADS1015_CHANNELS; ++k) {
		data->channel_data[k].pga = ADS1015_DEFAULT_PGA;
		data->channel_data[k].data_rate = ADS1015_DEFAULT_DATA_RATE;
	}
}
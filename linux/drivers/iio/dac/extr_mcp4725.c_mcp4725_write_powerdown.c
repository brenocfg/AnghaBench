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
struct mcp4725_data {TYPE_1__* client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct mcp4725_data* iio_priv (struct iio_dev*) ; 
 int mcp4725_resume (int /*<<< orphan*/ *) ; 
 int mcp4725_suspend (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t mcp4725_write_powerdown(struct iio_dev *indio_dev,
	 uintptr_t private, const struct iio_chan_spec *chan,
	 const char *buf, size_t len)
{
	struct mcp4725_data *data = iio_priv(indio_dev);
	bool state;
	int ret;

	ret = strtobool(buf, &state);
	if (ret)
		return ret;

	if (state)
		ret = mcp4725_suspend(&data->client->dev);
	else
		ret = mcp4725_resume(&data->client->dev);
	if (ret < 0)
		return ret;

	return len;
}
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
struct cm3323_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM3323_CMD_CONF ; 
 int /*<<< orphan*/  CM3323_CONF_SD_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_word_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cm3323_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static void cm3323_disable(void *data)
{
	int ret;
	struct iio_dev *indio_dev = data;
	struct cm3323_data *cm_data = iio_priv(indio_dev);

	ret = i2c_smbus_write_word_data(cm_data->client, CM3323_CMD_CONF,
					CM3323_CONF_SD_BIT);
	if (ret < 0)
		dev_err(&cm_data->client->dev, "Error writing reg_conf\n");
}
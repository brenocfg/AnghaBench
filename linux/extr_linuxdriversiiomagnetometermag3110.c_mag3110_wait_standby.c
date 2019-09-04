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
struct mag3110_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MAG3110_SYSMOD ; 
 int MAG3110_SYSMOD_MODE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 

__attribute__((used)) static int mag3110_wait_standby(struct mag3110_data *data)
{
	int ret, tries = 30;

	/*
	 * Takes up to 1/ODR to come out of active mode into stby
	 * Longest expected period is 12.5seconds.
	 * We'll sleep for 500ms between checks
	 */
	while (tries-- > 0) {
		ret = i2c_smbus_read_byte_data(data->client, MAG3110_SYSMOD);
		if (ret < 0) {
			dev_err(&data->client->dev, "i2c error\n");
			return ret;
		}
		/* wait for standby */
		if ((ret & MAG3110_SYSMOD_MODE_MASK) == 0)
			break;

		msleep_interruptible(500);
	}

	if (tries < 0) {
		dev_err(&data->client->dev, "device not entering standby mode\n");
		return -EIO;
	}

	return 0;
}
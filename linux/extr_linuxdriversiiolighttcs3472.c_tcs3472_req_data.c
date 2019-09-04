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
struct tcs3472_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TCS3472_STATUS ; 
 int TCS3472_STATUS_AVALID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int tcs3472_req_data(struct tcs3472_data *data)
{
	int tries = 50;
	int ret;

	while (tries--) {
		ret = i2c_smbus_read_byte_data(data->client, TCS3472_STATUS);
		if (ret < 0)
			return ret;
		if (ret & TCS3472_STATUS_AVALID)
			break;
		msleep(20);
	}

	if (tries < 0) {
		dev_err(&data->client->dev, "data not ready\n");
		return -EIO;
	}

	return 0;
}
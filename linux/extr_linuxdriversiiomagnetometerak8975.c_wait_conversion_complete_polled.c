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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ak8975_data {TYPE_1__* def; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ctrl_regs; } ;

/* Variables and functions */
 scalar_t__ AK8975_CONVERSION_DONE_POLL_TIME ; 
 scalar_t__ AK8975_MAX_CONVERSION_TIMEOUT ; 
 int EINVAL ; 
 size_t ST1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 

__attribute__((used)) static int wait_conversion_complete_polled(struct ak8975_data *data)
{
	struct i2c_client *client = data->client;
	u8 read_status;
	u32 timeout_ms = AK8975_MAX_CONVERSION_TIMEOUT;
	int ret;

	/* Wait for the conversion to complete. */
	while (timeout_ms) {
		msleep(AK8975_CONVERSION_DONE_POLL_TIME);
		ret = i2c_smbus_read_byte_data(client,
					       data->def->ctrl_regs[ST1]);
		if (ret < 0) {
			dev_err(&client->dev, "Error in reading ST1\n");
			return ret;
		}
		read_status = ret;
		if (read_status)
			break;
		timeout_ms -= AK8975_CONVERSION_DONE_POLL_TIME;
	}
	if (!timeout_ms) {
		dev_err(&client->dev, "Conversion timeout happened\n");
		return -EINVAL;
	}

	return read_status;
}
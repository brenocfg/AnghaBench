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
typedef  int /*<<< orphan*/  u8 ;
struct apds9300_data {int power_state; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int APDS9300_CMD ; 
 int APDS9300_CONTROL ; 
 int /*<<< orphan*/  APDS9300_POWER_OFF ; 
 int /*<<< orphan*/  APDS9300_POWER_ON ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apds9300_set_power_state(struct apds9300_data *data, int state)
{
	int ret;
	u8 cmd;

	cmd = state ? APDS9300_POWER_ON : APDS9300_POWER_OFF;
	ret = i2c_smbus_write_byte_data(data->client,
			APDS9300_CONTROL | APDS9300_CMD, cmd);
	if (ret) {
		dev_err(&data->client->dev,
			"failed to set power state %d\n", state);
		return ret;
	}
	data->power_state = state;

	return 0;
}
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
struct kxcjk1013_data {scalar_t__ chipset; TYPE_1__* client; int /*<<< orphan*/  wake_thres; int /*<<< orphan*/  wake_dur; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int KXCJK1013_REG_WAKE_THRES ; 
 int KXCJK1013_REG_WAKE_TIMER ; 
 scalar_t__ KXTF9 ; 
 int KXTF9_REG_WAKE_THRESH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kxcjk1013_chip_update_thresholds(struct kxcjk1013_data *data)
{
	int waketh_reg, ret;

	ret = i2c_smbus_write_byte_data(data->client,
					KXCJK1013_REG_WAKE_TIMER,
					data->wake_dur);
	if (ret < 0) {
		dev_err(&data->client->dev,
			"Error writing reg_wake_timer\n");
		return ret;
	}

	waketh_reg = data->chipset == KXTF9 ?
		KXTF9_REG_WAKE_THRESH : KXCJK1013_REG_WAKE_THRES;
	ret = i2c_smbus_write_byte_data(data->client, waketh_reg,
					data->wake_thres);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error writing reg_wake_thres\n");
		return ret;
	}

	return 0;
}
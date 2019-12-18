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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ABX8XX_OSS_OMODE ; 
 int /*<<< orphan*/  ABX8XX_REG_OSS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abx80x_is_rc_mode(struct i2c_client *client)
{
	int flags = 0;

	flags =  i2c_smbus_read_byte_data(client, ABX8XX_REG_OSS);
	if (flags < 0) {
		dev_err(&client->dev,
			"Failed to read autocalibration attribute\n");
		return flags;
	}

	return (flags & ABX8XX_OSS_OMODE) ? 1 : 0;
}
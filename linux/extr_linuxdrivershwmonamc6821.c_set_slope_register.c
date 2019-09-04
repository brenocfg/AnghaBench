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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static inline ssize_t set_slope_register(struct i2c_client *client,
		u8 reg,
		u8 dpwm,
		u8 *ptemp)
{
	int dt;
	u8 tmp;

	dt = ptemp[2]-ptemp[1];
	for (tmp = 4; tmp > 0; tmp--) {
		if (dt * (0x20 >> tmp) >= dpwm)
			break;
	}
	tmp |= (ptemp[1] & 0x7C) << 1;
	if (i2c_smbus_write_byte_data(client,
			reg, tmp)) {
		dev_err(&client->dev, "Register write error, aborting.\n");
		return -EIO;
	}
	return 0;
}
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
struct i2c_client {int dummy; } ;
struct ef4_nic {int dummy; } ;
struct TYPE_2__ {struct i2c_client* hwmon_client; struct i2c_client* ioexp_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX664X_REG_RSL ; 
 int /*<<< orphan*/  P0_CONFIG ; 
 int /*<<< orphan*/  P0_OUT ; 
 int /*<<< orphan*/  P1_CONFIG ; 
 TYPE_1__* falcon_board (struct ef4_nic*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sfe4001_poweroff(struct ef4_nic *efx)
{
	struct i2c_client *ioexp_client = falcon_board(efx)->ioexp_client;
	struct i2c_client *hwmon_client = falcon_board(efx)->hwmon_client;

	/* Turn off all power rails and disable outputs */
	i2c_smbus_write_byte_data(ioexp_client, P0_OUT, 0xff);
	i2c_smbus_write_byte_data(ioexp_client, P1_CONFIG, 0xff);
	i2c_smbus_write_byte_data(ioexp_client, P0_CONFIG, 0xff);

	/* Clear any over-temperature alert */
	i2c_smbus_read_byte_data(hwmon_client, MAX664X_REG_RSL);
}
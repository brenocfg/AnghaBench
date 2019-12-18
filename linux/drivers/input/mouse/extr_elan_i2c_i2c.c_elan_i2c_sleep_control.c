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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_I2C_SLEEP ; 
 int /*<<< orphan*/  ETP_I2C_STAND_CMD ; 
 int /*<<< orphan*/  ETP_I2C_WAKE_UP ; 
 int elan_i2c_write_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elan_i2c_sleep_control(struct i2c_client *client, bool sleep)
{
	return elan_i2c_write_cmd(client, ETP_I2C_STAND_CMD,
				  sleep ? ETP_I2C_SLEEP : ETP_I2C_WAKE_UP);
}
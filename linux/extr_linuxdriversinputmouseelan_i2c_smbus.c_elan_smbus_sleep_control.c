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
 int /*<<< orphan*/  ETP_SMBUS_SLEEP_CMD ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elan_smbus_sleep_control(struct i2c_client *client, bool sleep)
{
	if (sleep)
		return i2c_smbus_write_byte(client, ETP_SMBUS_SLEEP_CMD);
	else
		return 0; /* XXX should we send ETP_SMBUS_ENABLE_TP here? */
}
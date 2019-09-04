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
 int /*<<< orphan*/  AL3320A_CONFIG_DISABLE ; 
 int /*<<< orphan*/  AL3320A_REG_CONFIG ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int al3320a_remove(struct i2c_client *client)
{
	return i2c_smbus_write_byte_data(client, AL3320A_REG_CONFIG,
					 AL3320A_CONFIG_DISABLE);
}
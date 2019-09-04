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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,int) ; 

__attribute__((used)) static u8 read_register(struct i2c_client *client, int addr)
{
	/* XXX: The chip ignores LSB of register address */
	return i2c_smbus_read_byte_data(client, addr << 1);
}
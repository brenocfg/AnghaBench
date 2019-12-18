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
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 

__attribute__((used)) static int adt7475_read_word(struct i2c_client *client, int reg)
{
	int val1, val2;

	val1 = i2c_smbus_read_byte_data(client, reg);
	if (val1 < 0)
		return val1;
	val2 = i2c_smbus_read_byte_data(client, reg + 1);
	if (val2 < 0)
		return val2;

	return val1 | (val2 << 8);
}
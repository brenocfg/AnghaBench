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
 int i2c_smbus_write_byte (struct i2c_client*,unsigned int) ; 

__attribute__((used)) static int i2c_write_le8(struct i2c_client *client, unsigned data)
{
	return i2c_smbus_write_byte(client, data);
}
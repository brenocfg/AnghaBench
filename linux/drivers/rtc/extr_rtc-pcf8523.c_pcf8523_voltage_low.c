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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CONTROL3 ; 
 int REG_CONTROL3_BLF ; 
 int pcf8523_read (struct i2c_client*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int pcf8523_voltage_low(struct i2c_client *client)
{
	u8 value;
	int err;

	err = pcf8523_read(client, REG_CONTROL3, &value);
	if (err < 0)
		return err;

	return !!(value & REG_CONTROL3_BLF);
}
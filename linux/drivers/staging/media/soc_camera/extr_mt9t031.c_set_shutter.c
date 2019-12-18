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
typedef  int u32 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9T031_SHUTTER_WIDTH ; 
 int /*<<< orphan*/  MT9T031_SHUTTER_WIDTH_UPPER ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int set_shutter(struct i2c_client *client, const u32 data)
{
	int ret;

	ret = reg_write(client, MT9T031_SHUTTER_WIDTH_UPPER, data >> 16);

	if (ret >= 0)
		ret = reg_write(client, MT9T031_SHUTTER_WIDTH, data & 0xffff);

	return ret;
}
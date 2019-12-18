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
struct device {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  REG_OFFSET ; 
 int REG_OFFSET_MODE ; 
 int pcf8523_read (struct i2c_client*,int /*<<< orphan*/ ,int*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int pcf8523_rtc_read_offset(struct device *dev, long *offset)
{
	struct i2c_client *client = to_i2c_client(dev);
	int err;
	u8 value;
	s8 val;

	err = pcf8523_read(client, REG_OFFSET, &value);
	if (err < 0)
		return err;

	/* sign extend the 7-bit offset value */
	val = value << 1;
	*offset = (value & REG_OFFSET_MODE ? 4069 : 4340) * (val >> 1);

	return 0;
}
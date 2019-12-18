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
typedef  long u8 ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (long,int) ; 
 int /*<<< orphan*/  REG_OFFSET ; 
 long REG_OFFSET_MODE ; 
 scalar_t__ abs (long) ; 
 long clamp (int /*<<< orphan*/ ,long,long) ; 
 int pcf8523_write (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int pcf8523_rtc_set_offset(struct device *dev, long offset)
{
	struct i2c_client *client = to_i2c_client(dev);
	long reg_m0, reg_m1;
	u8 value;

	reg_m0 = clamp(DIV_ROUND_CLOSEST(offset, 4340), -64L, 63L);
	reg_m1 = clamp(DIV_ROUND_CLOSEST(offset, 4069), -64L, 63L);

	if (abs(reg_m0 * 4340 - offset) < abs(reg_m1 * 4069 - offset))
		value = reg_m0 & 0x7f;
	else
		value = (reg_m1 & 0x7f) | REG_OFFSET_MODE;

	return pcf8523_write(client, REG_OFFSET, value);
}
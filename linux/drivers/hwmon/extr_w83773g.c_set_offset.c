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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * W83773_OFFSET_LSB ; 
 int /*<<< orphan*/ * W83773_OFFSET_MSB ; 
 long clamp_val (long,int,int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int set_offset(struct regmap *regmap, int index, long val)
{
	int ret;
	u8 high_byte;
	u8 low_byte;

	val = clamp_val(val, -127825, 127825);
	/* offset value equals to (high_byte << 3 | low_byte >> 5) * 125 */
	val /= 125;
	high_byte = val >> 3;
	low_byte = (val & 0x07) << 5;

	ret = regmap_write(regmap, W83773_OFFSET_MSB[index], high_byte);
	if (ret < 0)
		return ret;

	return regmap_write(regmap, W83773_OFFSET_LSB[index], low_byte);
}
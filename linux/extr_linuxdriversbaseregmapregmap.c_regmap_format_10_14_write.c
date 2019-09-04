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
typedef  unsigned int u8 ;
struct regmap {unsigned int* work_buf; } ;

/* Variables and functions */

__attribute__((used)) static void regmap_format_10_14_write(struct regmap *map,
				    unsigned int reg, unsigned int val)
{
	u8 *out = map->work_buf;

	out[2] = val;
	out[1] = (val >> 8) | (reg << 6);
	out[0] = reg >> 2;
}
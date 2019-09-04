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
typedef  int /*<<< orphan*/  u64 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int regmap_update_bits (struct regmap*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_tps68470_regmap_update_bits(struct regmap *regmap, int reg,
					int bitmask, u64 value)
{
	return regmap_update_bits(regmap, reg, bitmask, value);
}
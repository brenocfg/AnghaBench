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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W83773_CONVERSION_RATE_REG_WRITE ; 
 int __fls (long) ; 
 int clamp_val (long,int,int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_update_interval(struct regmap *regmap, long val)
{
	int rate;

	/*
	 * For valid rates, interval can be calculated as
	 *	interval = (1 << (8 - rate)) * 62.5;
	 * Rounded rate is therefore
	 *	rate = 8 - __fls(interval * 8 / (62.5 * 7));
	 * Use clamp_val() to avoid overflows, and to ensure valid input
	 * for __fls.
	 */
	val = clamp_val(val, 62, 16000) * 10;
	rate = 8 - __fls((val * 8 / (625 * 7)));
	return regmap_write(regmap, W83773_CONVERSION_RATE_REG_WRITE, rate);
}
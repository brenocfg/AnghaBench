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
struct as3711 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int,unsigned int) ; 

__attribute__((used)) static int as3711_set_brightness_v(struct as3711 *as3711,
				   unsigned int brightness,
				   unsigned int reg)
{
	if (brightness > 31)
		return -EINVAL;

	return regmap_update_bits(as3711->regmap, reg, 0xf0,
				  brightness << 4);
}
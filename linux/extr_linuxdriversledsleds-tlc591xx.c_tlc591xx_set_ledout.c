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
struct tlc591xx_priv {int reg_ledout_offset; int /*<<< orphan*/  regmap; } ;
struct tlc591xx_led {int led_no; } ;

/* Variables and functions */
 unsigned int LEDOUT_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int
tlc591xx_set_ledout(struct tlc591xx_priv *priv, struct tlc591xx_led *led,
		    u8 val)
{
	unsigned int i = (led->led_no % 4) * 2;
	unsigned int mask = LEDOUT_MASK << i;
	unsigned int addr = priv->reg_ledout_offset + (led->led_no >> 2);

	val = val << i;

	return regmap_update_bits(priv->regmap, addr, mask, val);
}
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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct mvebu_gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvebu_gpioreg_level_mask (struct mvebu_gpio_chip*,struct regmap**,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvebu_gpio_write_level_mask(struct mvebu_gpio_chip *mvchip, u32 val)
{
	struct regmap *map;
	unsigned int offset;

	mvebu_gpioreg_level_mask(mvchip, &map, &offset);
	regmap_write(map, offset, val);
}
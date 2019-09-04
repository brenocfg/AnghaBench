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
 int /*<<< orphan*/  regmap_read (struct regmap*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
mvebu_gpio_read_level_mask(struct mvebu_gpio_chip *mvchip)
{
	struct regmap *map;
	unsigned int offset;
	u32 val;

	mvebu_gpioreg_level_mask(mvchip, &map, &offset);
	regmap_read(map, offset, &val);

	return val;
}
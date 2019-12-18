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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct ocelot {size_t** map; int /*<<< orphan*/ * targets; } ;

/* Variables and functions */
 size_t REG_MASK ; 
 size_t TARGET_OFFSET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,size_t,size_t,size_t) ; 

void __ocelot_rmw_ix(struct ocelot *ocelot, u32 val, u32 mask, u32 reg,
		     u32 offset)
{
	u16 target = reg >> TARGET_OFFSET;

	WARN_ON(!target);

	regmap_update_bits(ocelot->targets[target],
			   ocelot->map[target][reg & REG_MASK] + offset,
			   mask, val);
}
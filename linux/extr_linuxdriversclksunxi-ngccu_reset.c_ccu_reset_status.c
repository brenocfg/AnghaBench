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
struct reset_controller_dev {int dummy; } ;
struct ccu_reset_map {int bit; scalar_t__ reg; } ;
struct ccu_reset {scalar_t__ base; struct ccu_reset_map* reset_map; } ;

/* Variables and functions */
 struct ccu_reset* rcdev_to_ccu_reset (struct reset_controller_dev*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int ccu_reset_status(struct reset_controller_dev *rcdev,
			    unsigned long id)
{
	struct ccu_reset *ccu = rcdev_to_ccu_reset(rcdev);
	const struct ccu_reset_map *map = &ccu->reset_map[id];

	/*
	 * The reset control API expects 0 if reset is not asserted,
	 * which is the opposite of what our hardware uses.
	 */
	return !(map->bit & readl(ccu->base + map->reg));
}
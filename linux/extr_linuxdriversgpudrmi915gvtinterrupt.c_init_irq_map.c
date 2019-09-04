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
struct intel_gvt_irq_map {int up_irq_bit; size_t up_irq_group; size_t down_irq_group; int /*<<< orphan*/  down_irq_bitmask; } ;
struct intel_gvt_irq_info {int has_upstream_irq; int /*<<< orphan*/  group; int /*<<< orphan*/  downstream_irq_bitmap; } ;
struct intel_gvt_irq {struct intel_gvt_irq_info** info; struct intel_gvt_irq_map* irq_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  gvt_dbg_irq (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_irq_map(struct intel_gvt_irq *irq)
{
	struct intel_gvt_irq_map *map;
	struct intel_gvt_irq_info *up_info, *down_info;
	int up_bit;

	for (map = irq->irq_map; map->up_irq_bit != -1; map++) {
		up_info = irq->info[map->up_irq_group];
		up_bit = map->up_irq_bit;
		down_info = irq->info[map->down_irq_group];

		set_bit(up_bit, up_info->downstream_irq_bitmap);
		down_info->has_upstream_irq = true;

		gvt_dbg_irq("[up] grp %d bit %d -> [down] grp %d bitmask %x\n",
			up_info->group, up_bit,
			down_info->group, map->down_irq_bitmask);
	}
}
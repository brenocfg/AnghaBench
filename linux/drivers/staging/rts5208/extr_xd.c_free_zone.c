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
struct zone_entry {int /*<<< orphan*/ * free_table; int /*<<< orphan*/ * l2p_table; scalar_t__ unused_blk_cnt; scalar_t__ get_index; scalar_t__ set_index; scalar_t__ build_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void free_zone(struct zone_entry *zone)
{
	if (!zone)
		return;

	zone->build_flag = 0;
	zone->set_index = 0;
	zone->get_index = 0;
	zone->unused_blk_cnt = 0;
	vfree(zone->l2p_table);
	zone->l2p_table = NULL;
	vfree(zone->free_table);
	zone->free_table = NULL;
}
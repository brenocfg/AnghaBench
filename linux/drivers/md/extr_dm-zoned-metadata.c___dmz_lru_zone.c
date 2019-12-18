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
struct dmz_metadata {int /*<<< orphan*/  map_rnd_list; int /*<<< orphan*/  map_seq_list; } ;
struct dm_zone {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 scalar_t__ dmz_is_seq (struct dm_zone*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dmz_lru_zone(struct dmz_metadata *zmd, struct dm_zone *zone)
{
	if (list_empty(&zone->link))
		return;

	list_del_init(&zone->link);
	if (dmz_is_seq(zone)) {
		/* LRU rotate sequential zone */
		list_add_tail(&zone->link, &zmd->map_seq_list);
	} else {
		/* LRU rotate random zone */
		list_add_tail(&zone->link, &zmd->map_rnd_list);
	}
}
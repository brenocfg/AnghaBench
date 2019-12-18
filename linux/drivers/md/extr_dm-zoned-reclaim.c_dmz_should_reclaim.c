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
struct dmz_reclaim {struct dmz_metadata* metadata; } ;
struct dmz_metadata {int dummy; } ;

/* Variables and functions */
 unsigned int DMZ_RECLAIM_HIGH_UNMAP_RND ; 
 unsigned int DMZ_RECLAIM_LOW_UNMAP_RND ; 
 unsigned int dmz_nr_rnd_zones (struct dmz_metadata*) ; 
 unsigned int dmz_nr_unmap_rnd_zones (struct dmz_metadata*) ; 
 scalar_t__ dmz_target_idle (struct dmz_reclaim*) ; 

__attribute__((used)) static bool dmz_should_reclaim(struct dmz_reclaim *zrc)
{
	struct dmz_metadata *zmd = zrc->metadata;
	unsigned int nr_rnd = dmz_nr_rnd_zones(zmd);
	unsigned int nr_unmap_rnd = dmz_nr_unmap_rnd_zones(zmd);
	unsigned int p_unmap_rnd = nr_unmap_rnd * 100 / nr_rnd;

	/* Reclaim when idle */
	if (dmz_target_idle(zrc) && nr_unmap_rnd < nr_rnd)
		return true;

	/* If there are still plenty of random zones, do not reclaim */
	if (p_unmap_rnd >= DMZ_RECLAIM_HIGH_UNMAP_RND)
		return false;

	/*
	 * If the percentage of unmapped random zones is low,
	 * reclaim even if the target is busy.
	 */
	return p_unmap_rnd <= DMZ_RECLAIM_LOW_UNMAP_RND;
}
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
struct dmz_metadata {struct dmz_mblock** map_mblk; } ;
struct dmz_mblock {scalar_t__ data; } ;
struct dmz_map {void* bzone_id; void* dzone_id; } ;

/* Variables and functions */
 unsigned int DMZ_MAP_ENTRIES_MASK ; 
 unsigned int DMZ_MAP_ENTRIES_SHIFT ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  dmz_dirty_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 

__attribute__((used)) static void dmz_set_chunk_mapping(struct dmz_metadata *zmd, unsigned int chunk,
				  unsigned int dzone_id, unsigned int bzone_id)
{
	struct dmz_mblock *dmap_mblk = zmd->map_mblk[chunk >> DMZ_MAP_ENTRIES_SHIFT];
	struct dmz_map *dmap = (struct dmz_map *) dmap_mblk->data;
	int map_idx = chunk & DMZ_MAP_ENTRIES_MASK;

	dmap[map_idx].dzone_id = cpu_to_le32(dzone_id);
	dmap[map_idx].bzone_id = cpu_to_le32(bzone_id);
	dmz_dirty_mblock(zmd, dmap_mblk);
}
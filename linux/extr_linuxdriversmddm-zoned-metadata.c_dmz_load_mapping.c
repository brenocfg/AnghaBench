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
struct dmz_metadata {unsigned int nr_chunks; scalar_t__ nr_reserved_seq; int /*<<< orphan*/  unmap_nr_seq; int /*<<< orphan*/  unmap_seq_list; int /*<<< orphan*/  nr_seq; int /*<<< orphan*/  nr_reserved_seq_zones; int /*<<< orphan*/  reserved_seq_zones_list; int /*<<< orphan*/  unmap_nr_rnd; int /*<<< orphan*/  unmap_rnd_list; int /*<<< orphan*/  nr_rnd; int /*<<< orphan*/  map_rnd_list; int /*<<< orphan*/  map_seq_list; struct dmz_mblock** map_mblk; int /*<<< orphan*/  nr_map_blocks; struct dmz_dev* dev; } ;
struct dmz_mblock {scalar_t__ data; } ;
struct dmz_mblk {int dummy; } ;
struct dmz_map {int /*<<< orphan*/  bzone_id; int /*<<< orphan*/  dzone_id; } ;
struct dmz_dev {unsigned int nr_zones; } ;
struct dm_zone {unsigned int chunk; int /*<<< orphan*/  link; int /*<<< orphan*/  flags; struct dm_zone* bzone; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_BUF ; 
 int /*<<< orphan*/  DMZ_DATA ; 
 unsigned int DMZ_MAP_ENTRIES ; 
 unsigned int DMZ_MAP_UNMAPPED ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dmz_mblock*) ; 
 int PTR_ERR (struct dmz_mblock*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmz_dev_err (struct dmz_dev*,char*,unsigned int,unsigned int) ; 
 struct dm_zone* dmz_get (struct dmz_metadata*,unsigned int) ; 
 struct dmz_mblock* dmz_get_mblock (struct dmz_metadata*,unsigned int) ; 
 int /*<<< orphan*/  dmz_get_zone_weight (struct dmz_metadata*,struct dm_zone*) ; 
 scalar_t__ dmz_is_data (struct dm_zone*) ; 
 scalar_t__ dmz_is_meta (struct dm_zone*) ; 
 scalar_t__ dmz_is_rnd (struct dm_zone*) ; 
 struct dmz_mblock** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmz_load_mapping(struct dmz_metadata *zmd)
{
	struct dmz_dev *dev = zmd->dev;
	struct dm_zone *dzone, *bzone;
	struct dmz_mblock *dmap_mblk = NULL;
	struct dmz_map *dmap;
	unsigned int i = 0, e = 0, chunk = 0;
	unsigned int dzone_id;
	unsigned int bzone_id;

	/* Metadata block array for the chunk mapping table */
	zmd->map_mblk = kcalloc(zmd->nr_map_blocks,
				sizeof(struct dmz_mblk *), GFP_KERNEL);
	if (!zmd->map_mblk)
		return -ENOMEM;

	/* Get chunk mapping table blocks and initialize zone mapping */
	while (chunk < zmd->nr_chunks) {
		if (!dmap_mblk) {
			/* Get mapping block */
			dmap_mblk = dmz_get_mblock(zmd, i + 1);
			if (IS_ERR(dmap_mblk))
				return PTR_ERR(dmap_mblk);
			zmd->map_mblk[i] = dmap_mblk;
			dmap = (struct dmz_map *) dmap_mblk->data;
			i++;
			e = 0;
		}

		/* Check data zone */
		dzone_id = le32_to_cpu(dmap[e].dzone_id);
		if (dzone_id == DMZ_MAP_UNMAPPED)
			goto next;

		if (dzone_id >= dev->nr_zones) {
			dmz_dev_err(dev, "Chunk %u mapping: invalid data zone ID %u",
				    chunk, dzone_id);
			return -EIO;
		}

		dzone = dmz_get(zmd, dzone_id);
		set_bit(DMZ_DATA, &dzone->flags);
		dzone->chunk = chunk;
		dmz_get_zone_weight(zmd, dzone);

		if (dmz_is_rnd(dzone))
			list_add_tail(&dzone->link, &zmd->map_rnd_list);
		else
			list_add_tail(&dzone->link, &zmd->map_seq_list);

		/* Check buffer zone */
		bzone_id = le32_to_cpu(dmap[e].bzone_id);
		if (bzone_id == DMZ_MAP_UNMAPPED)
			goto next;

		if (bzone_id >= dev->nr_zones) {
			dmz_dev_err(dev, "Chunk %u mapping: invalid buffer zone ID %u",
				    chunk, bzone_id);
			return -EIO;
		}

		bzone = dmz_get(zmd, bzone_id);
		if (!dmz_is_rnd(bzone)) {
			dmz_dev_err(dev, "Chunk %u mapping: invalid buffer zone %u",
				    chunk, bzone_id);
			return -EIO;
		}

		set_bit(DMZ_DATA, &bzone->flags);
		set_bit(DMZ_BUF, &bzone->flags);
		bzone->chunk = chunk;
		bzone->bzone = dzone;
		dzone->bzone = bzone;
		dmz_get_zone_weight(zmd, bzone);
		list_add_tail(&bzone->link, &zmd->map_rnd_list);
next:
		chunk++;
		e++;
		if (e >= DMZ_MAP_ENTRIES)
			dmap_mblk = NULL;
	}

	/*
	 * At this point, only meta zones and mapped data zones were
	 * fully initialized. All remaining zones are unmapped data
	 * zones. Finish initializing those here.
	 */
	for (i = 0; i < dev->nr_zones; i++) {
		dzone = dmz_get(zmd, i);
		if (dmz_is_meta(dzone))
			continue;

		if (dmz_is_rnd(dzone))
			zmd->nr_rnd++;
		else
			zmd->nr_seq++;

		if (dmz_is_data(dzone)) {
			/* Already initialized */
			continue;
		}

		/* Unmapped data zone */
		set_bit(DMZ_DATA, &dzone->flags);
		dzone->chunk = DMZ_MAP_UNMAPPED;
		if (dmz_is_rnd(dzone)) {
			list_add_tail(&dzone->link, &zmd->unmap_rnd_list);
			atomic_inc(&zmd->unmap_nr_rnd);
		} else if (atomic_read(&zmd->nr_reserved_seq_zones) < zmd->nr_reserved_seq) {
			list_add_tail(&dzone->link, &zmd->reserved_seq_zones_list);
			atomic_inc(&zmd->nr_reserved_seq_zones);
			zmd->nr_seq--;
		} else {
			list_add_tail(&dzone->link, &zmd->unmap_seq_list);
			atomic_inc(&zmd->unmap_nr_seq);
		}
	}

	return 0;
}
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
struct sm_ftl {int cache_zone; int cache_block; int /*<<< orphan*/  mutex; } ;
struct mtd_blktrans_dev {struct sm_ftl* priv; } ;
struct ftl_zone {int* lba_to_phys_table; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct ftl_zone*) ; 
 int PTR_ERR (struct ftl_zone*) ; 
 int /*<<< orphan*/  SM_SECTOR_SIZE ; 
 int /*<<< orphan*/  memset (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sm_break_offset (struct sm_ftl*,unsigned long,int*,int*,int*) ; 
 int /*<<< orphan*/  sm_cache_get (struct sm_ftl*,char*,int) ; 
 int /*<<< orphan*/  sm_cache_put (struct sm_ftl*,char*,int) ; 
 struct ftl_zone* sm_get_zone (struct sm_ftl*,int) ; 
 scalar_t__ sm_read_sector (struct sm_ftl*,int,int,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sm_read(struct mtd_blktrans_dev *dev,
		   unsigned long sect_no, char *buf)
{
	struct sm_ftl *ftl = dev->priv;
	struct ftl_zone *zone;
	int error = 0, in_cache = 0;
	int zone_num, block, boffset;

	sm_break_offset(ftl, sect_no << 9, &zone_num, &block, &boffset);
	mutex_lock(&ftl->mutex);


	zone = sm_get_zone(ftl, zone_num);
	if (IS_ERR(zone)) {
		error = PTR_ERR(zone);
		goto unlock;
	}

	/* Have to look at cache first */
	if (ftl->cache_zone == zone_num && ftl->cache_block == block) {
		in_cache = 1;
		if (!sm_cache_get(ftl, buf, boffset))
			goto unlock;
	}

	/* Translate the block and return if doesn't exist in the table */
	block = zone->lba_to_phys_table[block];

	if (block == -1) {
		memset(buf, 0xFF, SM_SECTOR_SIZE);
		goto unlock;
	}

	if (sm_read_sector(ftl, zone_num, block, boffset, buf, NULL)) {
		error = -EIO;
		goto unlock;
	}

	if (in_cache)
		sm_cache_put(ftl, buf, boffset);
unlock:
	mutex_unlock(&ftl->mutex);
	return error;
}
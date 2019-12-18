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
typedef  void* uint16_t ;
struct sm_oob {int dummy; } ;
struct sm_ftl {int max_lba; int zone_size; void* cis_block; struct ftl_zone* zones; } ;
struct ftl_zone {void** lba_to_phys_table; int initialized; int /*<<< orphan*/  free_sectors; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  dbg_verbose (char*,void*,int) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 scalar_t__ kfifo_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int kfifo_len (int /*<<< orphan*/ *) ; 
 int kfifo_out (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void**,int,int) ; 
 scalar_t__ sm_block_erased (struct sm_oob*) ; 
 int /*<<< orphan*/  sm_block_valid (struct sm_oob*) ; 
 scalar_t__ sm_check_block (struct sm_ftl*,int,void*) ; 
 int /*<<< orphan*/  sm_erase_block (struct sm_ftl*,int,void*,int) ; 
 int /*<<< orphan*/  sm_printk (char*,...) ; 
 int sm_read_lba (struct sm_oob*) ; 
 scalar_t__ sm_read_sector (struct sm_ftl*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sm_oob*) ; 

__attribute__((used)) static int sm_init_zone(struct sm_ftl *ftl, int zone_num)
{
	struct ftl_zone *zone = &ftl->zones[zone_num];
	struct sm_oob oob;
	uint16_t block;
	int lba;
	int i = 0;
	int len;

	dbg("initializing zone %d", zone_num);

	/* Allocate memory for FTL table */
	zone->lba_to_phys_table = kmalloc_array(ftl->max_lba, 2, GFP_KERNEL);

	if (!zone->lba_to_phys_table)
		return -ENOMEM;
	memset(zone->lba_to_phys_table, -1, ftl->max_lba * 2);


	/* Allocate memory for free sectors FIFO */
	if (kfifo_alloc(&zone->free_sectors, ftl->zone_size * 2, GFP_KERNEL)) {
		kfree(zone->lba_to_phys_table);
		return -ENOMEM;
	}

	/* Now scan the zone */
	for (block = 0 ; block < ftl->zone_size ; block++) {

		/* Skip blocks till the CIS (including) */
		if (zone_num == 0 && block <= ftl->cis_block)
			continue;

		/* Read the oob of first sector */
		if (sm_read_sector(ftl, zone_num, block, 0, NULL, &oob)) {
			kfifo_free(&zone->free_sectors);
			kfree(zone->lba_to_phys_table);
			return -EIO;
		}

		/* Test to see if block is erased. It is enough to test
			first sector, because erase happens in one shot */
		if (sm_block_erased(&oob)) {
			kfifo_in(&zone->free_sectors,
				(unsigned char *)&block, 2);
			continue;
		}

		/* If block is marked as bad, skip it */
		/* This assumes we can trust first sector*/
		/* However the way the block valid status is defined, ensures
			very low probability of failure here */
		if (!sm_block_valid(&oob)) {
			dbg("PH %04d <-> <marked bad>", block);
			continue;
		}


		lba = sm_read_lba(&oob);

		/* Invalid LBA means that block is damaged. */
		/* We can try to erase it, or mark it as bad, but
			lets leave that to recovery application */
		if (lba == -2 || lba >= ftl->max_lba) {
			dbg("PH %04d <-> LBA %04d(bad)", block, lba);
			continue;
		}


		/* If there is no collision,
			just put the sector in the FTL table */
		if (zone->lba_to_phys_table[lba] < 0) {
			dbg_verbose("PH %04d <-> LBA %04d", block, lba);
			zone->lba_to_phys_table[lba] = block;
			continue;
		}

		sm_printk("collision"
			" of LBA %d between blocks %d and %d in zone %d",
			lba, zone->lba_to_phys_table[lba], block, zone_num);

		/* Test that this block is valid*/
		if (sm_check_block(ftl, zone_num, block))
			continue;

		/* Test now the old block */
		if (sm_check_block(ftl, zone_num,
					zone->lba_to_phys_table[lba])) {
			zone->lba_to_phys_table[lba] = block;
			continue;
		}

		/* If both blocks are valid and share same LBA, it means that
			they hold different versions of same data. It not
			known which is more recent, thus just erase one of them
		*/
		sm_printk("both blocks are valid, erasing the later");
		sm_erase_block(ftl, zone_num, block, 1);
	}

	dbg("zone initialized");
	zone->initialized = 1;

	/* No free sectors, means that the zone is heavily damaged, write won't
		work, but it can still can be (partially) read */
	if (!kfifo_len(&zone->free_sectors)) {
		sm_printk("no free blocks in zone %d", zone_num);
		return 0;
	}

	/* Randomize first block we write to */
	get_random_bytes(&i, 2);
	i %= (kfifo_len(&zone->free_sectors) / 2);

	while (i--) {
		len = kfifo_out(&zone->free_sectors,
					(unsigned char *)&block, 2);
		WARN_ON(len != 2);
		kfifo_in(&zone->free_sectors, (const unsigned char *)&block, 2);
	}
	return 0;
}
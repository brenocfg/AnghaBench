#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct dmz_metadata {int nr_meta_zones; int mblk_primary; scalar_t__ sb_gen; TYPE_2__* dev; TYPE_1__* sb; int /*<<< orphan*/  sb_zone; } ;
struct TYPE_7__ {int /*<<< orphan*/  gen; } ;
struct TYPE_6__ {int zone_nr_blocks_shift; } ;
struct TYPE_5__ {TYPE_4__* sb; scalar_t__ block; } ;

/* Variables and functions */
 int EIO ; 
 int dmz_check_sb (struct dmz_metadata*,TYPE_4__*) ; 
 int /*<<< orphan*/  dmz_dev_debug (TYPE_2__*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  dmz_dev_err (TYPE_2__*,char*) ; 
 int dmz_get_sb (struct dmz_metadata*,int) ; 
 int dmz_lookup_secondary_sb (struct dmz_metadata*) ; 
 int dmz_recover_mblocks (struct dmz_metadata*,int) ; 
 scalar_t__ dmz_start_block (struct dmz_metadata*,int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmz_load_sb(struct dmz_metadata *zmd)
{
	bool sb_good[2] = {false, false};
	u64 sb_gen[2] = {0, 0};
	int ret;

	/* Read and check the primary super block */
	zmd->sb[0].block = dmz_start_block(zmd, zmd->sb_zone);
	ret = dmz_get_sb(zmd, 0);
	if (ret) {
		dmz_dev_err(zmd->dev, "Read primary super block failed");
		return ret;
	}

	ret = dmz_check_sb(zmd, zmd->sb[0].sb);

	/* Read and check secondary super block */
	if (ret == 0) {
		sb_good[0] = true;
		zmd->sb[1].block = zmd->sb[0].block +
			(zmd->nr_meta_zones << zmd->dev->zone_nr_blocks_shift);
		ret = dmz_get_sb(zmd, 1);
	} else
		ret = dmz_lookup_secondary_sb(zmd);

	if (ret) {
		dmz_dev_err(zmd->dev, "Read secondary super block failed");
		return ret;
	}

	ret = dmz_check_sb(zmd, zmd->sb[1].sb);
	if (ret == 0)
		sb_good[1] = true;

	/* Use highest generation sb first */
	if (!sb_good[0] && !sb_good[1]) {
		dmz_dev_err(zmd->dev, "No valid super block found");
		return -EIO;
	}

	if (sb_good[0])
		sb_gen[0] = le64_to_cpu(zmd->sb[0].sb->gen);
	else
		ret = dmz_recover_mblocks(zmd, 0);

	if (sb_good[1])
		sb_gen[1] = le64_to_cpu(zmd->sb[1].sb->gen);
	else
		ret = dmz_recover_mblocks(zmd, 1);

	if (ret) {
		dmz_dev_err(zmd->dev, "Recovery failed");
		return -EIO;
	}

	if (sb_gen[0] >= sb_gen[1]) {
		zmd->sb_gen = sb_gen[0];
		zmd->mblk_primary = 0;
	} else {
		zmd->sb_gen = sb_gen[1];
		zmd->mblk_primary = 1;
	}

	dmz_dev_debug(zmd->dev, "Using super block %u (gen %llu)",
		      zmd->mblk_primary, zmd->sb_gen);

	return 0;
}
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
struct list_head {int dummy; } ;
struct dmz_metadata {int mblk_primary; } ;

/* Variables and functions */
 int dmz_write_dirty_mblocks (struct dmz_metadata*,struct list_head*,unsigned int) ; 
 int dmz_write_sb (struct dmz_metadata*,unsigned int) ; 

__attribute__((used)) static int dmz_log_dirty_mblocks(struct dmz_metadata *zmd,
				 struct list_head *write_list)
{
	unsigned int log_set = zmd->mblk_primary ^ 0x1;
	int ret;

	/* Write dirty blocks to the log */
	ret = dmz_write_dirty_mblocks(zmd, write_list, log_set);
	if (ret)
		return ret;

	/*
	 * No error so far: now validate the log by updating the
	 * log index super block generation.
	 */
	ret = dmz_write_sb(zmd, log_set);
	if (ret)
		return ret;

	return 0;
}
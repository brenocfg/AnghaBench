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
typedef  scalar_t__ u16 ;
struct super_block {int dummy; } ;
struct file_dentry_t {int /*<<< orphan*/  checksum; scalar_t__ num_ext; } ;
struct dentry_t {int dummy; } ;
struct chain_t {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CS_DEFAULT ; 
 int /*<<< orphan*/  CS_DIR_ENTRY ; 
 int /*<<< orphan*/  DENTRY_SIZE ; 
 int /*<<< orphan*/  SET16_A (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  buf_lock (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_modify (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_unlock (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ calc_checksum_2byte (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 

void update_dir_checksum(struct super_block *sb, struct chain_t *p_dir,
			 s32 entry)
{
	int i, num_entries;
	sector_t sector;
	u16 chksum;
	struct file_dentry_t *file_ep;
	struct dentry_t *ep;

	file_ep = (struct file_dentry_t *)get_entry_in_dir(sb, p_dir, entry,
							   &sector);
	if (!file_ep)
		return;

	buf_lock(sb, sector);

	num_entries = (s32)file_ep->num_ext + 1;
	chksum = calc_checksum_2byte((void *)file_ep, DENTRY_SIZE, 0,
				     CS_DIR_ENTRY);

	for (i = 1; i < num_entries; i++) {
		ep = get_entry_in_dir(sb, p_dir, entry + i, NULL);
		if (!ep) {
			buf_unlock(sb, sector);
			return;
		}

		chksum = calc_checksum_2byte((void *)ep, DENTRY_SIZE, chksum,
					     CS_DEFAULT);
	}

	SET16_A(file_ep->checksum, chksum);
	buf_modify(sb, sector);
	buf_unlock(sb, sector);
}
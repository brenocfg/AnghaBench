#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fs_info_t {int cluster_size_bits; int cluster_size; int /*<<< orphan*/  v_sem; scalar_t__ dev_ejected; } ;
struct file_id_t {scalar_t__ type; int rwoffset; int size; int flags; scalar_t__ hint_last_off; int /*<<< orphan*/  hint_last_clu; int /*<<< orphan*/  start_clu; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct bd_info_t {scalar_t__ sector_size_bits; scalar_t__ sector_size_mask; scalar_t__ sector_size; } ;
typedef  scalar_t__ sector_t ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int FAT_read (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FFS_EOF ; 
 int FFS_ERROR ; 
 int FFS_INVALIDFID ; 
 int FFS_MEDIAERR ; 
 int FFS_PERMISSIONERR ; 
 scalar_t__ FFS_SUCCESS ; 
 scalar_t__ START_SECTOR (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_FILE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 scalar_t__ sector_read (struct super_block*,scalar_t__,struct buffer_head**,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffsReadFile(struct inode *inode, struct file_id_t *fid, void *buffer,
		       u64 count, u64 *rcount)
{
	s32 offset, sec_offset, clu_offset;
	u32 clu;
	int ret = 0;
	sector_t LogSector;
	u64 oneblkread, read_bytes;
	struct buffer_head *tmp_bh = NULL;
	struct super_block *sb = inode->i_sb;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	/* check the validity of the given file id */
	if (!fid)
		return FFS_INVALIDFID;

	/* check the validity of pointer parameters */
	if (!buffer)
		return FFS_ERROR;

	/* acquire the lock for file system critical section */
	down(&p_fs->v_sem);

	/* check if the given file ID is opened */
	if (fid->type != TYPE_FILE) {
		ret = FFS_PERMISSIONERR;
		goto out;
	}

	if (fid->rwoffset > fid->size)
		fid->rwoffset = fid->size;

	if (count > (fid->size - fid->rwoffset))
		count = fid->size - fid->rwoffset;

	if (count == 0) {
		if (rcount)
			*rcount = 0;
		ret = FFS_EOF;
		goto out;
	}

	read_bytes = 0;

	while (count > 0) {
		clu_offset = (s32)(fid->rwoffset >> p_fs->cluster_size_bits);
		clu = fid->start_clu;

		if (fid->flags == 0x03) {
			clu += clu_offset;
		} else {
			/* hint information */
			if ((clu_offset > 0) && (fid->hint_last_off > 0) &&
			    (clu_offset >= fid->hint_last_off)) {
				clu_offset -= fid->hint_last_off;
				clu = fid->hint_last_clu;
			}

			while (clu_offset > 0) {
				/* clu = FAT_read(sb, clu); */
				if (FAT_read(sb, clu, &clu) == -1)
					return FFS_MEDIAERR;

				clu_offset--;
			}
		}

		/* hint information */
		fid->hint_last_off = (s32)(fid->rwoffset >>
					   p_fs->cluster_size_bits);
		fid->hint_last_clu = clu;

		/* byte offset in cluster */
		offset = (s32)(fid->rwoffset & (p_fs->cluster_size - 1));

		/* sector offset in cluster */
		sec_offset = offset >> p_bd->sector_size_bits;

		/* byte offset in sector */
		offset &= p_bd->sector_size_mask;

		LogSector = START_SECTOR(clu) + sec_offset;

		oneblkread = (u64)(p_bd->sector_size - offset);
		if (oneblkread > count)
			oneblkread = count;

		if ((offset == 0) && (oneblkread == p_bd->sector_size)) {
			if (sector_read(sb, LogSector, &tmp_bh, 1) !=
			    FFS_SUCCESS)
				goto err_out;
			memcpy((char *)buffer + read_bytes,
			       (char *)tmp_bh->b_data, (s32)oneblkread);
		} else {
			if (sector_read(sb, LogSector, &tmp_bh, 1) !=
			    FFS_SUCCESS)
				goto err_out;
			memcpy((char *)buffer + read_bytes,
			       (char *)tmp_bh->b_data + offset,
			       (s32)oneblkread);
		}
		count -= oneblkread;
		read_bytes += oneblkread;
		fid->rwoffset += oneblkread;
	}
	brelse(tmp_bh);

/* How did this ever work and not leak a brlse()?? */
err_out:
	/* set the size of read bytes */
	if (rcount)
		*rcount = read_bytes;

	if (p_fs->dev_ejected)
		ret = FFS_MEDIAERR;

out:
	/* release the lock for file system critical section */
	up(&p_fs->v_sem);

	return ret;
}
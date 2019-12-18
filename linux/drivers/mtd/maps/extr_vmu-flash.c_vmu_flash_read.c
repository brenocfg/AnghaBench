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
typedef  int /*<<< orphan*/  u_char ;
struct vmu_cache {scalar_t__ block; scalar_t__ buffer; scalar_t__ jiffies_atc; scalar_t__ valid; } ;
struct vmu_block {scalar_t__ num; size_t ofs; } ;
struct mtd_info {struct mdev_part* priv; } ;
struct memcard {int blocklen; TYPE_1__* parts; } ;
struct mdev_part {int partition; struct maple_device* mdev; } ;
struct maple_device {int dummy; } ;
typedef  size_t loff_t ;
struct TYPE_2__ {int numblocks; struct vmu_cache* pcache; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct vmu_block*) ; 
 struct memcard* maple_get_drvdata (struct maple_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,unsigned char,int) ; 
 struct vmu_block* ofs_to_block (size_t,struct mtd_info*,int) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char vmu_flash_read_char (size_t,int*,struct mtd_info*) ; 

__attribute__((used)) static int vmu_flash_read(struct mtd_info *mtd, loff_t from, size_t len,
	size_t *retlen,  u_char *buf)
{
	struct maple_device *mdev;
	struct memcard *card;
	struct mdev_part *mpart;
	struct vmu_cache *pcache;
	struct vmu_block *vblock;
	int index = 0, retval, partition, leftover, numblocks;
	unsigned char cx;

	mpart = mtd->priv;
	mdev = mpart->mdev;
	partition = mpart->partition;
	card = maple_get_drvdata(mdev);

	numblocks = card->parts[partition].numblocks;
	if (from + len > numblocks * card->blocklen)
		len = numblocks * card->blocklen - from;
	if (len == 0)
		return -EIO;
	/* Have we cached this bit already? */
	pcache = card->parts[partition].pcache;
	do {
		vblock =  ofs_to_block(from + index, mtd, partition);
		if (!vblock)
			return -ENOMEM;
		/* Have we cached this and is the cache valid and timely? */
		if (pcache->valid &&
			time_before(jiffies, pcache->jiffies_atc + HZ) &&
			(pcache->block == vblock->num)) {
			/* we have cached it, so do necessary copying */
			leftover = card->blocklen - vblock->ofs;
			if (vblock->ofs + len - index < card->blocklen) {
				/* only a bit of this block to copy */
				memcpy(buf + index,
					pcache->buffer + vblock->ofs,
					len - index);
				index = len;
			} else {
				/* otherwise copy remainder of whole block */
				memcpy(buf + index, pcache->buffer +
					vblock->ofs, leftover);
				index += leftover;
			}
		} else {
			/*
			* Not cached so read one byte -
			* but cache the rest of the block
			*/
			cx = vmu_flash_read_char(from + index, &retval, mtd);
			if (retval) {
				*retlen = index;
				kfree(vblock);
				return cx;
			}
			memset(buf + index, cx, 1);
			index++;
		}
		kfree(vblock);
	} while (len > index);
	*retlen = index;

	return 0;
}
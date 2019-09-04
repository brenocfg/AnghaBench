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
struct vmupart {unsigned short user_blocks; unsigned short root_block; int numblocks; struct vmu_cache* name; struct vmu_cache* pcache; } ;
struct vmu_cache {size_t partition; struct maple_device* mdev; } ;
struct mtd_info {int type; int flags; int size; int erasesize; int writesize; struct vmu_cache* priv; int /*<<< orphan*/  owner; int /*<<< orphan*/  _sync; int /*<<< orphan*/  _read; int /*<<< orphan*/  _write; struct vmu_cache* name; } ;
struct memcard {unsigned short tempA; unsigned short tempB; size_t partition; int blocklen; size_t partitions; struct mtd_info* mtd; struct vmupart* parts; } ;
struct mdev_part {size_t partition; struct maple_device* mdev; } ;
struct mapleq {TYPE_1__* recvbuf; struct maple_device* dev; } ;
struct maple_device {int port; int unit; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAPLE_COMMAND_GETMINFO ; 
 int /*<<< orphan*/  MAPLE_FUNC_MEMCARD ; 
 int MTD_NO_ERASE ; 
 int MTD_WRITEABLE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,size_t,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  kfree (struct vmu_cache*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct vmu_cache* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_add_packet (struct maple_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct memcard* maple_get_drvdata (struct maple_device*) ; 
 int /*<<< orphan*/  maple_getcond_callback (struct maple_device*,void (*) (struct mapleq*),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (struct vmu_cache*,char*,int,int,size_t) ; 
 int /*<<< orphan*/  vmu_flash_read ; 
 int /*<<< orphan*/  vmu_flash_sync ; 
 int /*<<< orphan*/  vmu_flash_write ; 

__attribute__((used)) static void vmu_queryblocks(struct mapleq *mq)
{
	struct maple_device *mdev;
	unsigned short *res;
	struct memcard *card;
	__be32 partnum;
	struct vmu_cache *pcache;
	struct mdev_part *mpart;
	struct mtd_info *mtd_cur;
	struct vmupart *part_cur;
	int error;

	mdev = mq->dev;
	card = maple_get_drvdata(mdev);
	res = (unsigned short *) (mq->recvbuf->buf);
	card->tempA = res[12];
	card->tempB = res[6];

	dev_info(&mdev->dev, "VMU device at partition %d has %d user "
		"blocks with a root block at %d\n", card->partition,
		card->tempA, card->tempB);

	part_cur = &card->parts[card->partition];
	part_cur->user_blocks = card->tempA;
	part_cur->root_block = card->tempB;
	part_cur->numblocks = card->tempB + 1;
	part_cur->name = kmalloc(12, GFP_KERNEL);
	if (!part_cur->name)
		goto fail_name;

	sprintf(part_cur->name, "vmu%d.%d.%d",
		mdev->port, mdev->unit, card->partition);
	mtd_cur = &card->mtd[card->partition];
	mtd_cur->name = part_cur->name;
	mtd_cur->type = 8;
	mtd_cur->flags = MTD_WRITEABLE|MTD_NO_ERASE;
	mtd_cur->size = part_cur->numblocks * card->blocklen;
	mtd_cur->erasesize = card->blocklen;
	mtd_cur->_write = vmu_flash_write;
	mtd_cur->_read = vmu_flash_read;
	mtd_cur->_sync = vmu_flash_sync;
	mtd_cur->writesize = card->blocklen;

	mpart = kmalloc(sizeof(struct mdev_part), GFP_KERNEL);
	if (!mpart)
		goto fail_mpart;

	mpart->mdev = mdev;
	mpart->partition = card->partition;
	mtd_cur->priv = mpart;
	mtd_cur->owner = THIS_MODULE;

	pcache = kzalloc(sizeof(struct vmu_cache), GFP_KERNEL);
	if (!pcache)
		goto fail_cache_create;
	part_cur->pcache = pcache;

	error = mtd_device_register(mtd_cur, NULL, 0);
	if (error)
		goto fail_mtd_register;

	maple_getcond_callback(mdev, NULL, 0,
		MAPLE_FUNC_MEMCARD);

	/*
	* Set up a recursive call to the (probably theoretical)
	* second or more partition
	*/
	if (++card->partition < card->partitions) {
		partnum = cpu_to_be32(card->partition << 24);
		maple_getcond_callback(mdev, vmu_queryblocks, 0,
			MAPLE_FUNC_MEMCARD);
		maple_add_packet(mdev, MAPLE_FUNC_MEMCARD,
			MAPLE_COMMAND_GETMINFO, 2, &partnum);
	}
	return;

fail_mtd_register:
	dev_err(&mdev->dev, "Could not register maple device at (%d, %d)"
		"error is 0x%X\n", mdev->port, mdev->unit, error);
	for (error = 0; error <= card->partition; error++) {
		kfree(((card->parts)[error]).pcache);
		((card->parts)[error]).pcache = NULL;
	}
fail_cache_create:
fail_mpart:
	for (error = 0; error <= card->partition; error++) {
		kfree(((card->mtd)[error]).priv);
		((card->mtd)[error]).priv = NULL;
	}
	maple_getcond_callback(mdev, NULL, 0,
		MAPLE_FUNC_MEMCARD);
	kfree(part_cur->name);
fail_name:
	return;
}
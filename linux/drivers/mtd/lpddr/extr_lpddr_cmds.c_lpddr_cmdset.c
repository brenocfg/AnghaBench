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
struct mtd_info {int size; int erasesize; int writesize; int numchips; int chipshift; struct flchip* chips; TYPE_1__* qinfo; int /*<<< orphan*/  _unpoint; int /*<<< orphan*/  _point; int /*<<< orphan*/  _unlock; int /*<<< orphan*/  _lock; int /*<<< orphan*/  _writev; int /*<<< orphan*/  _write; int /*<<< orphan*/  _erase; int /*<<< orphan*/  flags; void* type; int /*<<< orphan*/  _read; struct map_info* priv; } ;
struct map_info {struct mtd_info* fldrv_priv; } ;
struct lpddr_private {int size; int erasesize; int writesize; int numchips; int chipshift; struct flchip* chips; TYPE_1__* qinfo; int /*<<< orphan*/  _unpoint; int /*<<< orphan*/  _point; int /*<<< orphan*/  _unlock; int /*<<< orphan*/  _lock; int /*<<< orphan*/  _writev; int /*<<< orphan*/  _write; int /*<<< orphan*/  _erase; int /*<<< orphan*/  flags; void* type; int /*<<< orphan*/  _read; struct map_info* priv; } ;
struct flchip_shared {int /*<<< orphan*/  lock; int /*<<< orphan*/ * erasing; int /*<<< orphan*/  writing; } ;
struct flchip {int start; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wq; struct flchip_shared* priv; int /*<<< orphan*/  state; int /*<<< orphan*/  oldstate; } ;
struct TYPE_2__ {int DevSizeShift; int UniformBlockSizeShift; int BufSizeShift; int HWPartsNum; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_READY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_BIT_WRITEABLE ; 
 int /*<<< orphan*/  MTD_CAP_NORFLASH ; 
 void* MTD_NORFLASH ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mtd_info*) ; 
 struct flchip_shared* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct mtd_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpddr_erase ; 
 int /*<<< orphan*/  lpddr_lock ; 
 int /*<<< orphan*/  lpddr_point ; 
 int /*<<< orphan*/  lpddr_read ; 
 int /*<<< orphan*/  lpddr_unlock ; 
 int /*<<< orphan*/  lpddr_unpoint ; 
 int /*<<< orphan*/  lpddr_write_buffers ; 
 int /*<<< orphan*/  lpddr_writev ; 
 scalar_t__ map_is_linear (struct map_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct mtd_info *lpddr_cmdset(struct map_info *map)
{
	struct lpddr_private *lpddr = map->fldrv_priv;
	struct flchip_shared *shared;
	struct flchip *chip;
	struct mtd_info *mtd;
	int numchips;
	int i, j;

	mtd = kzalloc(sizeof(*mtd), GFP_KERNEL);
	if (!mtd)
		return NULL;
	mtd->priv = map;
	mtd->type = MTD_NORFLASH;

	/* Fill in the default mtd operations */
	mtd->_read = lpddr_read;
	mtd->type = MTD_NORFLASH;
	mtd->flags = MTD_CAP_NORFLASH;
	mtd->flags &= ~MTD_BIT_WRITEABLE;
	mtd->_erase = lpddr_erase;
	mtd->_write = lpddr_write_buffers;
	mtd->_writev = lpddr_writev;
	mtd->_lock = lpddr_lock;
	mtd->_unlock = lpddr_unlock;
	if (map_is_linear(map)) {
		mtd->_point = lpddr_point;
		mtd->_unpoint = lpddr_unpoint;
	}
	mtd->size = 1 << lpddr->qinfo->DevSizeShift;
	mtd->erasesize = 1 << lpddr->qinfo->UniformBlockSizeShift;
	mtd->writesize = 1 << lpddr->qinfo->BufSizeShift;

	shared = kmalloc_array(lpddr->numchips, sizeof(struct flchip_shared),
						GFP_KERNEL);
	if (!shared) {
		kfree(lpddr);
		kfree(mtd);
		return NULL;
	}

	chip = &lpddr->chips[0];
	numchips = lpddr->numchips / lpddr->qinfo->HWPartsNum;
	for (i = 0; i < numchips; i++) {
		shared[i].writing = shared[i].erasing = NULL;
		mutex_init(&shared[i].lock);
		for (j = 0; j < lpddr->qinfo->HWPartsNum; j++) {
			*chip = lpddr->chips[i];
			chip->start += j << lpddr->chipshift;
			chip->oldstate = chip->state = FL_READY;
			chip->priv = &shared[i];
			/* those should be reset too since
			   they create memory references. */
			init_waitqueue_head(&chip->wq);
			mutex_init(&chip->mutex);
			chip++;
		}
	}

	return mtd;
}
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
struct TYPE_2__ {struct device* parent; } ;
struct mtd_info {char* name; int writesize; int writebufsize; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; int /*<<< orphan*/  _erase; int /*<<< orphan*/  erasesize; int /*<<< orphan*/  size; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; TYPE_1__ dev; struct bcm47xxsflash* priv; } ;
struct device {int dummy; } ;
struct bcm47xxsflash {int /*<<< orphan*/  blocksize; int /*<<< orphan*/  size; struct mtd_info mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_CAP_NORFLASH ; 
 int /*<<< orphan*/  MTD_NORFLASH ; 
 int /*<<< orphan*/  bcm47xxsflash_erase ; 
 int /*<<< orphan*/  bcm47xxsflash_read ; 
 int /*<<< orphan*/  bcm47xxsflash_write ; 

__attribute__((used)) static void bcm47xxsflash_fill_mtd(struct bcm47xxsflash *b47s,
				   struct device *dev)
{
	struct mtd_info *mtd = &b47s->mtd;

	mtd->priv = b47s;
	mtd->dev.parent = dev;
	mtd->name = "bcm47xxsflash";

	mtd->type = MTD_NORFLASH;
	mtd->flags = MTD_CAP_NORFLASH;
	mtd->size = b47s->size;
	mtd->erasesize = b47s->blocksize;
	mtd->writesize = 1;
	mtd->writebufsize = 1;

	mtd->_erase = bcm47xxsflash_erase;
	mtd->_read = bcm47xxsflash_read;
	mtd->_write = bcm47xxsflash_write;
}
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
typedef  int uint32_t ;
struct sst25l_flash {int /*<<< orphan*/  lock; TYPE_1__* spi; } ;
struct mtd_info {int erasesize; } ;
struct erase_info {int len; int addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sst25l_erase_sector (struct sst25l_flash*,int) ; 
 int sst25l_wait_till_ready (struct sst25l_flash*) ; 
 struct sst25l_flash* to_sst25l_flash (struct mtd_info*) ; 

__attribute__((used)) static int sst25l_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct sst25l_flash *flash = to_sst25l_flash(mtd);
	uint32_t addr, end;
	int err;

	/* Sanity checks */
	if ((uint32_t)instr->len % mtd->erasesize)
		return -EINVAL;

	if ((uint32_t)instr->addr % mtd->erasesize)
		return -EINVAL;

	addr = instr->addr;
	end = addr + instr->len;

	mutex_lock(&flash->lock);

	err = sst25l_wait_till_ready(flash);
	if (err) {
		mutex_unlock(&flash->lock);
		return err;
	}

	while (addr < end) {
		err = sst25l_erase_sector(flash, addr);
		if (err) {
			mutex_unlock(&flash->lock);
			dev_err(&flash->spi->dev, "Erase failed\n");
			return err;
		}

		addr += mtd->erasesize;
	}

	mutex_unlock(&flash->lock);

	return 0;
}
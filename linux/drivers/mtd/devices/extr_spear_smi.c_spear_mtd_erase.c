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
typedef  int u32 ;
struct spear_snor_flash {int bank; int /*<<< orphan*/  lock; } ;
struct spear_smi {int num_flashes; TYPE_1__* pdev; } ;
struct mtd_info {scalar_t__ erasesize; struct spear_smi* priv; } ;
struct erase_info {int addr; int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct spear_snor_flash* get_flash_data (struct mtd_info*) ; 
 int get_sector_erase_cmd (struct spear_snor_flash*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spear_smi_erase_sector (struct spear_smi*,int,int,int) ; 

__attribute__((used)) static int spear_mtd_erase(struct mtd_info *mtd, struct erase_info *e_info)
{
	struct spear_snor_flash *flash = get_flash_data(mtd);
	struct spear_smi *dev = mtd->priv;
	u32 addr, command, bank;
	int len, ret;

	if (!flash || !dev)
		return -ENODEV;

	bank = flash->bank;
	if (bank > dev->num_flashes - 1) {
		dev_err(&dev->pdev->dev, "Invalid Bank Num");
		return -EINVAL;
	}

	addr = e_info->addr;
	len = e_info->len;

	mutex_lock(&flash->lock);

	/* now erase sectors in loop */
	while (len) {
		command = get_sector_erase_cmd(flash, addr);
		/* preparing the command for flash */
		ret = spear_smi_erase_sector(dev, bank, command, 4);
		if (ret) {
			mutex_unlock(&flash->lock);
			return ret;
		}
		addr += mtd->erasesize;
		len -= mtd->erasesize;
	}

	mutex_unlock(&flash->lock);

	return 0;
}
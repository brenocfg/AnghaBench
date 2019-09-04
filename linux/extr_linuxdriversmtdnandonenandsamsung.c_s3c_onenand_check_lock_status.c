#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct onenand_chip {unsigned int chipsize; unsigned int erase_shift; } ;
struct mtd_info {struct onenand_chip* priv; } ;
struct device {int dummy; } ;
struct TYPE_5__ {unsigned int (* mem_addr ) (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* pdev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MAP_01 (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  INT_ERR_ACK_OFFSET ; 
 int /*<<< orphan*/  INT_ERR_STAT_OFFSET ; 
 int LOCKED_BLK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 TYPE_2__* onenand ; 
 int s3c_read_cmd (int /*<<< orphan*/ ) ; 
 int s3c_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_write_reg (int,int /*<<< orphan*/ ) ; 
 unsigned int stub1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c_onenand_check_lock_status(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;
	struct device *dev = &onenand->pdev->dev;
	unsigned int block, end;
	int tmp;

	end = this->chipsize >> this->erase_shift;

	for (block = 0; block < end; block++) {
		unsigned int mem_addr = onenand->mem_addr(block, 0, 0);
		tmp = s3c_read_cmd(CMD_MAP_01(onenand, mem_addr));

		if (s3c_read_reg(INT_ERR_STAT_OFFSET) & LOCKED_BLK) {
			dev_err(dev, "block %d is write-protected!\n", block);
			s3c_write_reg(LOCKED_BLK, INT_ERR_ACK_OFFSET);
		}
	}
}
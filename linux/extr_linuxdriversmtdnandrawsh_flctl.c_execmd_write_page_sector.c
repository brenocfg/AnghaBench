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
struct sh_flctl {int seqin_page_addr; scalar_t__ page_size; } ;
struct mtd_info {scalar_t__ writesize; } ;

/* Variables and functions */
 int ACM_SACCES_MODE ; 
 int /*<<< orphan*/  FLADR (struct sh_flctl*) ; 
 int /*<<< orphan*/  FLCMDCR (struct sh_flctl*) ; 
 int /*<<< orphan*/  FLCMNCR (struct sh_flctl*) ; 
 int NAND_CMD_PAGEPROG ; 
 int NAND_CMD_SEQIN ; 
 int /*<<< orphan*/  empty_fifo (struct sh_flctl*) ; 
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cmd_regs (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  start_translation (struct sh_flctl*) ; 
 int /*<<< orphan*/  wait_completion (struct sh_flctl*) ; 
 int /*<<< orphan*/  write_ec_fiforeg (struct sh_flctl*,int,scalar_t__) ; 
 int /*<<< orphan*/  write_fiforeg (struct sh_flctl*,int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void execmd_write_page_sector(struct mtd_info *mtd)
{
	struct sh_flctl *flctl = mtd_to_flctl(mtd);
	int page_addr = flctl->seqin_page_addr;
	int sector, page_sectors;

	page_sectors = flctl->page_size ? 4 : 1;

	set_cmd_regs(mtd, NAND_CMD_PAGEPROG,
			(NAND_CMD_PAGEPROG << 8) | NAND_CMD_SEQIN);

	empty_fifo(flctl);
	writel(readl(FLCMNCR(flctl)) | ACM_SACCES_MODE, FLCMNCR(flctl));
	writel(readl(FLCMDCR(flctl)) | page_sectors, FLCMDCR(flctl));
	writel(page_addr << 2, FLADR(flctl));
	start_translation(flctl);

	for (sector = 0; sector < page_sectors; sector++) {
		write_fiforeg(flctl, 512, 512 * sector);
		write_ec_fiforeg(flctl, 16, mtd->writesize + 16 * sector);
	}

	wait_completion(flctl);
	writel(readl(FLCMNCR(flctl)) & ~ACM_SACCES_MODE, FLCMNCR(flctl));
}
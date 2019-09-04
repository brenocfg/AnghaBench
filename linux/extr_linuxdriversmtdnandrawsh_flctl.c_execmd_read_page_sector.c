#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_flctl {TYPE_1__* pdev; int /*<<< orphan*/ * done_buff; scalar_t__ page_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  failed; int /*<<< orphan*/  corrected; } ;
struct mtd_info {int writesize; TYPE_2__ ecc_stats; } ;
typedef  enum flctl_ecc_res_t { ____Placeholder_flctl_ecc_res_t } flctl_ecc_res_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ACM_SACCES_MODE ; 
 int /*<<< orphan*/  FLADR (struct sh_flctl*) ; 
 int /*<<< orphan*/  FLCMDCR (struct sh_flctl*) ; 
 int /*<<< orphan*/  FLCMNCR (struct sh_flctl*) ; 
#define  FL_ERROR 129 
#define  FL_REPAIRABLE 128 
 int NAND_CMD_READ0 ; 
 int NAND_CMD_READSTART ; 
 int _4ECCCORRECT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  empty_fifo (struct sh_flctl*) ; 
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 int read_ecfiforeg (struct sh_flctl*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_fiforeg (struct sh_flctl*,int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cmd_regs (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  start_translation (struct sh_flctl*) ; 
 int /*<<< orphan*/  wait_completion (struct sh_flctl*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void execmd_read_page_sector(struct mtd_info *mtd, int page_addr)
{
	struct sh_flctl *flctl = mtd_to_flctl(mtd);
	int sector, page_sectors;
	enum flctl_ecc_res_t ecc_result;

	page_sectors = flctl->page_size ? 4 : 1;

	set_cmd_regs(mtd, NAND_CMD_READ0,
		(NAND_CMD_READSTART << 8) | NAND_CMD_READ0);

	writel(readl(FLCMNCR(flctl)) | ACM_SACCES_MODE | _4ECCCORRECT,
		 FLCMNCR(flctl));
	writel(readl(FLCMDCR(flctl)) | page_sectors, FLCMDCR(flctl));
	writel(page_addr << 2, FLADR(flctl));

	empty_fifo(flctl);
	start_translation(flctl);

	for (sector = 0; sector < page_sectors; sector++) {
		read_fiforeg(flctl, 512, 512 * sector);

		ecc_result = read_ecfiforeg(flctl,
			&flctl->done_buff[mtd->writesize + 16 * sector],
			sector);

		switch (ecc_result) {
		case FL_REPAIRABLE:
			dev_info(&flctl->pdev->dev,
				"applied ecc on page 0x%x", page_addr);
			mtd->ecc_stats.corrected++;
			break;
		case FL_ERROR:
			dev_warn(&flctl->pdev->dev,
				"page 0x%x contains corrupted data\n",
				page_addr);
			mtd->ecc_stats.failed++;
			break;
		default:
			;
		}
	}

	wait_completion(flctl);

	writel(readl(FLCMNCR(flctl)) & ~(ACM_SACCES_MODE | _4ECCCORRECT),
			FLCMNCR(flctl));
}
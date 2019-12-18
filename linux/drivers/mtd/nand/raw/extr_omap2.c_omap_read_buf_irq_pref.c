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
struct TYPE_2__ {int options; } ;
struct omap_nand_info {int buf_len; TYPE_1__ nand; int /*<<< orphan*/  gpmc_cs; int /*<<< orphan*/  comp; int /*<<< orphan*/  gpmc_irq_fifo; int /*<<< orphan*/  gpmc_irq_count; int /*<<< orphan*/ * buf; int /*<<< orphan*/  iomode; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  OMAP_NAND_IO_READ ; 
 int PREFETCH_FIFOTHRESHOLD_MAX ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct omap_nand_info* mtd_to_omap (struct mtd_info*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int omap_prefetch_enable (int /*<<< orphan*/ ,int,int,int,int,struct omap_nand_info*) ; 
 int /*<<< orphan*/  omap_prefetch_reset (int /*<<< orphan*/ ,struct omap_nand_info*) ; 
 int /*<<< orphan*/  omap_read_buf16 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  omap_read_buf8 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  omap_read_buf_pref (struct nand_chip*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_read_buf_irq_pref(struct nand_chip *chip, u_char *buf,
				   int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct omap_nand_info *info = mtd_to_omap(mtd);
	int ret = 0;

	if (len <= mtd->oobsize) {
		omap_read_buf_pref(chip, buf, len);
		return;
	}

	info->iomode = OMAP_NAND_IO_READ;
	info->buf = buf;
	init_completion(&info->comp);

	/*  configure and start prefetch transfer */
	ret = omap_prefetch_enable(info->gpmc_cs,
			PREFETCH_FIFOTHRESHOLD_MAX/2, 0x0, len, 0x0, info);
	if (ret)
		/* PFPW engine is busy, use cpu copy method */
		goto out_copy;

	info->buf_len = len;

	enable_irq(info->gpmc_irq_count);
	enable_irq(info->gpmc_irq_fifo);

	/* waiting for read to complete */
	wait_for_completion(&info->comp);

	/* disable and stop the PFPW engine */
	omap_prefetch_reset(info->gpmc_cs, info);
	return;

out_copy:
	if (info->nand.options & NAND_BUSWIDTH_16)
		omap_read_buf16(mtd, buf, len);
	else
		omap_read_buf8(mtd, buf, len);
}
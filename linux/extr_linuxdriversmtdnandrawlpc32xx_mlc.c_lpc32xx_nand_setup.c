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
struct lpc32xx_nand_host {int /*<<< orphan*/  io_base; TYPE_1__* ncfg; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int tcea_delay; int busy_delay; int nand_ta; int rd_high; int rd_low; int wr_high; int wr_low; } ;

/* Variables and functions */
 int MLCCEH_NORMAL ; 
 int MLCCMD_RESET ; 
 int MLCICR_LARGEBLOCK ; 
 int MLCICR_LONGADDR ; 
 int MLCIRQ_CONTROLLER_READY ; 
 int MLCIRQ_NAND_READY ; 
 int /*<<< orphan*/  MLCLOCKPR_MAGIC ; 
 int MLCTIMEREG_BUSY_DELAY (int) ; 
 int MLCTIMEREG_NAND_TA (int) ; 
 int MLCTIMEREG_RD_HIGH (int) ; 
 int MLCTIMEREG_RD_LOW (int) ; 
 int MLCTIMEREG_TCEA_DELAY (int) ; 
 int MLCTIMEREG_WR_HIGH (int) ; 
 int MLCTIMEREG_WR_LOW (int) ; 
 int /*<<< orphan*/  MLC_CEH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLC_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLC_ICR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLC_IRQ_MR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLC_LOCK_PR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLC_TIME_REG (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpc32xx_nand_setup(struct lpc32xx_nand_host *host)
{
	uint32_t clkrate, tmp;

	/* Reset MLC controller */
	writel(MLCCMD_RESET, MLC_CMD(host->io_base));
	udelay(1000);

	/* Get base clock for MLC block */
	clkrate = clk_get_rate(host->clk);
	if (clkrate == 0)
		clkrate = 104000000;

	/* Unlock MLC_ICR
	 * (among others, will be locked again automatically) */
	writew(MLCLOCKPR_MAGIC, MLC_LOCK_PR(host->io_base));

	/* Configure MLC Controller: Large Block, 5 Byte Address */
	tmp = MLCICR_LARGEBLOCK | MLCICR_LONGADDR;
	writel(tmp, MLC_ICR(host->io_base));

	/* Unlock MLC_TIME_REG
	 * (among others, will be locked again automatically) */
	writew(MLCLOCKPR_MAGIC, MLC_LOCK_PR(host->io_base));

	/* Compute clock setup values, see LPC and NAND manual */
	tmp = 0;
	tmp |= MLCTIMEREG_TCEA_DELAY(clkrate / host->ncfg->tcea_delay + 1);
	tmp |= MLCTIMEREG_BUSY_DELAY(clkrate / host->ncfg->busy_delay + 1);
	tmp |= MLCTIMEREG_NAND_TA(clkrate / host->ncfg->nand_ta + 1);
	tmp |= MLCTIMEREG_RD_HIGH(clkrate / host->ncfg->rd_high + 1);
	tmp |= MLCTIMEREG_RD_LOW(clkrate / host->ncfg->rd_low);
	tmp |= MLCTIMEREG_WR_HIGH(clkrate / host->ncfg->wr_high + 1);
	tmp |= MLCTIMEREG_WR_LOW(clkrate / host->ncfg->wr_low);
	writel(tmp, MLC_TIME_REG(host->io_base));

	/* Enable IRQ for CONTROLLER_READY and NAND_READY */
	writeb(MLCIRQ_CONTROLLER_READY | MLCIRQ_NAND_READY,
			MLC_IRQ_MR(host->io_base));

	/* Normal nCE operation: nCE controlled by controller */
	writel(MLCCEH_NORMAL, MLC_CEH(host->io_base));
}
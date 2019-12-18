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
struct TYPE_2__ {int bpw; int mode; int prescale; int chip_select; } ;
struct fsl_lpspi_data {int /*<<< orphan*/  dev; scalar_t__ base; scalar_t__ is_first_byte; int /*<<< orphan*/  usedma; TYPE_1__ config; int /*<<< orphan*/  is_slave; } ;

/* Variables and functions */
 scalar_t__ IMX7ULP_TCR ; 
 int TCR_CONT ; 
 int TCR_CONTC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void fsl_lpspi_set_cmd(struct fsl_lpspi_data *fsl_lpspi)
{
	u32 temp = 0;

	temp |= fsl_lpspi->config.bpw - 1;
	temp |= (fsl_lpspi->config.mode & 0x3) << 30;
	if (!fsl_lpspi->is_slave) {
		temp |= fsl_lpspi->config.prescale << 27;
		temp |= (fsl_lpspi->config.chip_select & 0x3) << 24;

		/*
		 * Set TCR_CONT will keep SS asserted after current transfer.
		 * For the first transfer, clear TCR_CONTC to assert SS.
		 * For subsequent transfer, set TCR_CONTC to keep SS asserted.
		 */
		if (!fsl_lpspi->usedma) {
			temp |= TCR_CONT;
			if (fsl_lpspi->is_first_byte)
				temp &= ~TCR_CONTC;
			else
				temp |= TCR_CONTC;
		}
	}
	writel(temp, fsl_lpspi->base + IMX7ULP_TCR);

	dev_dbg(fsl_lpspi->dev, "TCR=0x%x\n", temp);
}
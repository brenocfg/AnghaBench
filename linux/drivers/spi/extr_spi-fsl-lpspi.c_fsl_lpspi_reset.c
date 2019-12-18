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
typedef  int u32 ;
struct fsl_lpspi_data {scalar_t__ base; int /*<<< orphan*/  usedma; } ;

/* Variables and functions */
 int CR_RRF ; 
 int CR_RTF ; 
 scalar_t__ IMX7ULP_CR ; 
 scalar_t__ IMX7ULP_SR ; 
 int /*<<< orphan*/  fsl_lpspi_intctrl (struct fsl_lpspi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int fsl_lpspi_reset(struct fsl_lpspi_data *fsl_lpspi)
{
	u32 temp;

	if (!fsl_lpspi->usedma) {
		/* Disable all interrupt */
		fsl_lpspi_intctrl(fsl_lpspi, 0);
	}

	/* W1C for all flags in SR */
	temp = 0x3F << 8;
	writel(temp, fsl_lpspi->base + IMX7ULP_SR);

	/* Clear FIFO and disable module */
	temp = CR_RRF | CR_RTF;
	writel(temp, fsl_lpspi->base + IMX7ULP_CR);

	return 0;
}
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
struct TYPE_2__ {int mode; } ;
struct fsl_lpspi_data {scalar_t__ base; scalar_t__ usedma; TYPE_1__ config; int /*<<< orphan*/  is_slave; } ;

/* Variables and functions */
 int CFGR1_MASTER ; 
 int CFGR1_PCSPOL ; 
 int CFGR1_PINCFG ; 
 int CR_MEN ; 
 int CR_RRF ; 
 int CR_RTF ; 
 int DER_RDDE ; 
 int DER_TDDE ; 
 scalar_t__ IMX7ULP_CFGR1 ; 
 scalar_t__ IMX7ULP_CR ; 
 scalar_t__ IMX7ULP_DER ; 
 int SPI_CS_HIGH ; 
 int fsl_lpspi_set_bitrate (struct fsl_lpspi_data*) ; 
 int /*<<< orphan*/  fsl_lpspi_set_watermark (struct fsl_lpspi_data*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int fsl_lpspi_config(struct fsl_lpspi_data *fsl_lpspi)
{
	u32 temp;
	int ret;

	if (!fsl_lpspi->is_slave) {
		ret = fsl_lpspi_set_bitrate(fsl_lpspi);
		if (ret)
			return ret;
	}

	fsl_lpspi_set_watermark(fsl_lpspi);

	if (!fsl_lpspi->is_slave)
		temp = CFGR1_MASTER;
	else
		temp = CFGR1_PINCFG;
	if (fsl_lpspi->config.mode & SPI_CS_HIGH)
		temp |= CFGR1_PCSPOL;
	writel(temp, fsl_lpspi->base + IMX7ULP_CFGR1);

	temp = readl(fsl_lpspi->base + IMX7ULP_CR);
	temp |= CR_RRF | CR_RTF | CR_MEN;
	writel(temp, fsl_lpspi->base + IMX7ULP_CR);

	temp = 0;
	if (fsl_lpspi->usedma)
		temp = DER_TDDE | DER_RDDE;
	writel(temp, fsl_lpspi->base + IMX7ULP_DER);

	return 0;
}
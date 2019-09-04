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
struct vpfe_ccdc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPFE_DMA_CNTL ; 
 int VPFE_DMA_CNTL_OVERFLOW ; 
 int /*<<< orphan*/  VPFE_PCR ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  vpfe_ccdc_restore_defaults (struct vpfe_ccdc*) ; 
 int /*<<< orphan*/  vpfe_config_enable (struct vpfe_ccdc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpfe_pcr_enable (struct vpfe_ccdc*,int /*<<< orphan*/ ) ; 
 int vpfe_reg_read (struct vpfe_ccdc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpfe_reg_write (struct vpfe_ccdc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_ccdc_close(struct vpfe_ccdc *ccdc, struct device *dev)
{
	int dma_cntl, i, pcr;

	/* If the CCDC module is still busy wait for it to be done */
	for (i = 0; i < 10; i++) {
		usleep_range(5000, 6000);
		pcr = vpfe_reg_read(ccdc, VPFE_PCR);
		if (!pcr)
			break;

		/* make sure it it is disabled */
		vpfe_pcr_enable(ccdc, 0);
	}

	/* Disable CCDC by resetting all register to default POR values */
	vpfe_ccdc_restore_defaults(ccdc);

	/* if DMA_CNTL overflow bit is set. Clear it
	 *  It appears to take a while for this to become quiescent ~20ms
	 */
	for (i = 0; i < 10; i++) {
		dma_cntl = vpfe_reg_read(ccdc, VPFE_DMA_CNTL);
		if (!(dma_cntl & VPFE_DMA_CNTL_OVERFLOW))
			break;

		/* Clear the overflow bit */
		vpfe_reg_write(ccdc, dma_cntl, VPFE_DMA_CNTL);
		usleep_range(5000, 6000);
	}

	/* Disabled the module at the CONFIG level */
	vpfe_config_enable(ccdc, 0);

	pm_runtime_put_sync(dev);

	return 0;
}
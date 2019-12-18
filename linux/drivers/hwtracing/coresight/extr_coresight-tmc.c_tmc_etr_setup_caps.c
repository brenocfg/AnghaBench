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
struct tmc_drvdata {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EACCES ; 
 int TMC_DEVID_AXIAW_MASK ; 
 int TMC_DEVID_AXIAW_SHIFT ; 
 int TMC_DEVID_AXIAW_VALID ; 
 int TMC_DEVID_NOSCAT ; 
 int /*<<< orphan*/  TMC_ETR_SG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tmc_drvdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ tmc_etr_can_use_sg (struct device*) ; 
 int /*<<< orphan*/  tmc_etr_has_non_secure_access (struct tmc_drvdata*) ; 
 int /*<<< orphan*/  tmc_etr_init_caps (struct tmc_drvdata*,int) ; 
 int /*<<< orphan*/  tmc_etr_set_cap (struct tmc_drvdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tmc_etr_setup_caps(struct device *parent, u32 devid, void *dev_caps)
{
	int rc;
	u32 dma_mask = 0;
	struct tmc_drvdata *drvdata = dev_get_drvdata(parent);

	if (!tmc_etr_has_non_secure_access(drvdata))
		return -EACCES;

	/* Set the unadvertised capabilities */
	tmc_etr_init_caps(drvdata, (u32)(unsigned long)dev_caps);

	if (!(devid & TMC_DEVID_NOSCAT) && tmc_etr_can_use_sg(parent))
		tmc_etr_set_cap(drvdata, TMC_ETR_SG);

	/* Check if the AXI address width is available */
	if (devid & TMC_DEVID_AXIAW_VALID)
		dma_mask = ((devid >> TMC_DEVID_AXIAW_SHIFT) &
				TMC_DEVID_AXIAW_MASK);

	/*
	 * Unless specified in the device configuration, ETR uses a 40-bit
	 * AXI master in place of the embedded SRAM of ETB/ETF.
	 */
	switch (dma_mask) {
	case 32:
	case 40:
	case 44:
	case 48:
	case 52:
		dev_info(parent, "Detected dma mask %dbits\n", dma_mask);
		break;
	default:
		dma_mask = 40;
	}

	rc = dma_set_mask_and_coherent(parent, DMA_BIT_MASK(dma_mask));
	if (rc)
		dev_err(parent, "Failed to setup DMA mask: %d\n", rc);
	return rc;
}
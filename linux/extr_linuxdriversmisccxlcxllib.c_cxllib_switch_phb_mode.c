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
struct pci_dev {int dummy; } ;
typedef  enum cxllib_mode { ____Placeholder_cxllib_mode } cxllib_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
#define  CXL_MODE_CXL 129 
 unsigned long CXL_MODE_DMA_TVT1 ; 
#define  CXL_MODE_PCI 128 
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  OPAL_PHB_CAPI_MODE_DMA_TVT1 ; 
 int /*<<< orphan*/  OPAL_PHB_CAPI_MODE_SNOOP_OFF ; 
 int /*<<< orphan*/  OPAL_PHB_CAPI_MODE_SNOOP_ON ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int pnv_phb_to_cxl_mode (struct pci_dev*,int /*<<< orphan*/ ) ; 

int cxllib_switch_phb_mode(struct pci_dev *dev, enum cxllib_mode mode,
			unsigned long flags)
{
	int rc = 0;

	if (!cpu_has_feature(CPU_FTR_HVMODE))
		return -EINVAL;

	switch (mode) {
	case CXL_MODE_PCI:
		/*
		 * We currently don't support going back to PCI mode
		 * However, we'll turn the invalidations off, so that
		 * the firmware doesn't have to ack them and can do
		 * things like reset, etc.. with no worries.
		 * So always return EPERM (can't go back to PCI) or
		 * EBUSY if we couldn't even turn off snooping
		 */
		rc = pnv_phb_to_cxl_mode(dev, OPAL_PHB_CAPI_MODE_SNOOP_OFF);
		if (rc)
			rc = -EBUSY;
		else
			rc = -EPERM;
		break;
	case CXL_MODE_CXL:
		/* DMA only supported on TVT1 for the time being */
		if (flags != CXL_MODE_DMA_TVT1)
			return -EINVAL;
		rc = pnv_phb_to_cxl_mode(dev, OPAL_PHB_CAPI_MODE_DMA_TVT1);
		if (rc)
			return rc;
		rc = pnv_phb_to_cxl_mode(dev, OPAL_PHB_CAPI_MODE_SNOOP_ON);
		break;
	default:
		rc = -EINVAL;
	}
	return rc;
}
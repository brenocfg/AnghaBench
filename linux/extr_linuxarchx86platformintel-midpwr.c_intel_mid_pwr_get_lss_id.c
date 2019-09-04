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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ERANGE ; 
 scalar_t__ INTEL_MID_PWR_LSS_OFFSET ; 
 int INTEL_MID_PWR_LSS_TYPE ; 
 int LSS_MAX_DEVS ; 
 int /*<<< orphan*/  PCI_CAP_ID_VNDR ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,int*) ; 

int intel_mid_pwr_get_lss_id(struct pci_dev *pdev)
{
	int vndr;
	u8 id;

	/*
	 * Mapping to PWRMU index is kept in the Logical SubSystem ID byte of
	 * Vendor capability.
	 */
	vndr = pci_find_capability(pdev, PCI_CAP_ID_VNDR);
	if (!vndr)
		return -EINVAL;

	/* Read the Logical SubSystem ID byte */
	pci_read_config_byte(pdev, vndr + INTEL_MID_PWR_LSS_OFFSET, &id);
	if (!(id & INTEL_MID_PWR_LSS_TYPE))
		return -ENODEV;

	id &= ~INTEL_MID_PWR_LSS_TYPE;
	if (id >= LSS_MAX_DEVS)
		return -ERANGE;

	return id;
}
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

/* Variables and functions */
 scalar_t__ IE31200_CAPID0 ; 
 unsigned char IE31200_CAPID0_ECC ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,unsigned char*) ; 

__attribute__((used)) static bool ecc_capable(struct pci_dev *pdev)
{
	unsigned char capid0_4b; /* 4th byte of CAPID0 */

	pci_read_config_byte(pdev, IE31200_CAPID0 + 3, &capid0_4b);
	if (capid0_4b & IE31200_CAPID0_ECC)
		return false;
	return true;
}
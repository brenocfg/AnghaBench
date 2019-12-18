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
 scalar_t__ mmio_enabled (struct pci_dev*) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static int mmio_resource_enabled(struct pci_dev *pdev, int idx)
{
	return pci_resource_start(pdev, idx) && mmio_enabled(pdev);
}
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
struct msix_entry {int dummy; } ;

/* Variables and functions */
 int __pci_enable_msix_range (struct pci_dev*,struct msix_entry*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pci_enable_msix_range(struct pci_dev *dev, struct msix_entry *entries,
		int minvec, int maxvec)
{
	return __pci_enable_msix_range(dev, entries, minvec, maxvec, NULL, 0);
}
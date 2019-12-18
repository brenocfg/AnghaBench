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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct umc_dev {TYPE_1__ dev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ dev_is_pci (int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct pci_dev *umc_parent_pci_dev(struct umc_dev *umc_dev)
{
	struct pci_dev *pci_dev = NULL;
	if (dev_is_pci(umc_dev->dev.parent))
		pci_dev = to_pci_dev(umc_dev->dev.parent);
	return pci_dev;
}
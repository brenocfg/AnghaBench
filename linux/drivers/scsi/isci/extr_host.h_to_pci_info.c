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
struct isci_pci_info {int dummy; } ;

/* Variables and functions */
 struct isci_pci_info* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static inline struct isci_pci_info *to_pci_info(struct pci_dev *pdev)
{
	return pci_get_drvdata(pdev);
}
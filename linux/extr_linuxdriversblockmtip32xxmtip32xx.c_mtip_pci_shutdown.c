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
struct driver_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtip_block_shutdown (struct driver_data*) ; 
 struct driver_data* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void mtip_pci_shutdown(struct pci_dev *pdev)
{
	struct driver_data *dd = pci_get_drvdata(pdev);
	if (dd)
		mtip_block_shutdown(dd);
}
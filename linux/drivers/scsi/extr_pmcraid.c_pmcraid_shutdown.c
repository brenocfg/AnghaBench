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
struct pmcraid_instance {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct pmcraid_instance* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pmcraid_reset_bringdown (struct pmcraid_instance*) ; 

__attribute__((used)) static void pmcraid_shutdown(struct pci_dev *pdev)
{
	struct pmcraid_instance *pinstance = pci_get_drvdata(pdev);
	pmcraid_reset_bringdown(pinstance);
}
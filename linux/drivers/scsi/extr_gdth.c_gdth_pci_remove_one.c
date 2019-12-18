#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ gdth_ha_str ;

/* Variables and functions */
 int /*<<< orphan*/  gdth_remove_one (TYPE_1__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 TYPE_1__* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void gdth_pci_remove_one(struct pci_dev *pdev)
{
	gdth_ha_str *ha = pci_get_drvdata(pdev);

	list_del(&ha->list);
	gdth_remove_one(ha);

	pci_disable_device(pdev);
}
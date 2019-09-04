#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ event; } ;
struct TYPE_4__ {TYPE_3__ power_state; } ;
struct TYPE_5__ {TYPE_1__ power; } ;
struct pci_dev {TYPE_2__ dev; } ;
typedef  int /*<<< orphan*/  pmac_ide_hwif_t ;

/* Variables and functions */
 TYPE_3__ PMSG_ON ; 
 scalar_t__ PM_EVENT_ON ; 
 int /*<<< orphan*/ * pci_get_drvdata (struct pci_dev*) ; 
 int pmac_ide_do_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pmac_ide_pci_resume(struct pci_dev *pdev)
{
	pmac_ide_hwif_t *pmif = pci_get_drvdata(pdev);
	int rc = 0;

	if (pdev->dev.power.power_state.event != PM_EVENT_ON) {
		rc = pmac_ide_do_resume(pmif);
		if (rc == 0)
			pdev->dev.power.power_state = PMSG_ON;
	}

	return rc;
}
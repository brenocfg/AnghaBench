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
struct sv_cable_table {scalar_t__ device; scalar_t__ subvendor; int (* cable_detect ) (struct ata_port*) ;} ;
struct pci_dev {scalar_t__ device; scalar_t__ subsystem_vendor; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ PCI_ANY_ID ; 
 struct sv_cable_table* cable_detect ; 
 int stub1 (struct ata_port*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serverworks_cable_detect(struct ata_port *ap)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	struct sv_cable_table *cb = cable_detect;

	while(cb->device) {
		if (cb->device == pdev->device &&
		    (cb->subvendor == pdev->subsystem_vendor ||
		      cb->subvendor == PCI_ANY_ID)) {
			return cb->cable_detect(ap);
		}
		cb++;
	}

	BUG();
	return -1;	/* kill compiler warning */
}
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
struct fm801_gp {int /*<<< orphan*/  res_port; int /*<<< orphan*/  gameport; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_unregister_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fm801_gp*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct fm801_gp* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm801_gp_remove(struct pci_dev *pci)
{
	struct fm801_gp *gp = pci_get_drvdata(pci);

	gameport_unregister_port(gp->gameport);
	release_resource(gp->res_port);
	kfree(gp);

	pci_disable_device(pci);
}
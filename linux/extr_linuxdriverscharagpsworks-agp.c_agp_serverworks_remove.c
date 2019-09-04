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
struct pci_dev {int dummy; } ;
struct agp_bridge_data {int /*<<< orphan*/ * dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * svrwrks_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_put_bridge (struct agp_bridge_data*) ; 
 int /*<<< orphan*/  agp_remove_bridge (struct agp_bridge_data*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ *) ; 
 struct agp_bridge_data* pci_get_drvdata (struct pci_dev*) ; 
 TYPE_1__ serverworks_private ; 

__attribute__((used)) static void agp_serverworks_remove(struct pci_dev *pdev)
{
	struct agp_bridge_data *bridge = pci_get_drvdata(pdev);

	pci_dev_put(bridge->dev);
	agp_remove_bridge(bridge);
	agp_put_bridge(bridge);
	pci_dev_put(serverworks_private.svrwrks_dev);
	serverworks_private.svrwrks_dev = NULL;
}
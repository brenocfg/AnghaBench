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
struct rocker_port {TYPE_1__* dev; struct rocker* rocker; } ;
struct rocker {struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_1__*) ; 
 int rocker_cmd_get_port_settings_macaddr (struct rocker_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rocker_port_dev_addr_init(struct rocker_port *rocker_port)
{
	const struct rocker *rocker = rocker_port->rocker;
	const struct pci_dev *pdev = rocker->pdev;
	int err;

	err = rocker_cmd_get_port_settings_macaddr(rocker_port,
						   rocker_port->dev->dev_addr);
	if (err) {
		dev_warn(&pdev->dev, "failed to get mac address, using random\n");
		eth_hw_addr_random(rocker_port->dev);
	}
}
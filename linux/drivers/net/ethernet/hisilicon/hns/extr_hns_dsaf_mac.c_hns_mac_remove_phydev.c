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
struct hns_mac_cb {int /*<<< orphan*/ * phy_dev; int /*<<< orphan*/  fw_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_device_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_device_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_acpi_device_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_mac_remove_phydev(struct hns_mac_cb *mac_cb)
{
	if (!to_acpi_device_node(mac_cb->fw_port) || !mac_cb->phy_dev)
		return;

	phy_device_remove(mac_cb->phy_dev);
	phy_device_free(mac_cb->phy_dev);

	mac_cb->phy_dev = NULL;
}
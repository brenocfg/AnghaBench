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
struct ql_adapter {int port_link_up; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STS ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_route_initialize (struct ql_adapter*) ; 
 int ql_set_mac_addr (struct ql_adapter*,int) ; 

int ql_cam_route_initialize(struct ql_adapter *qdev)
{
	int status, set;

	/* If check if the link is up and use to
	 * determine if we are setting or clearing
	 * the MAC address in the CAM.
	 */
	set = ql_read32(qdev, STS);
	set &= qdev->port_link_up;
	status = ql_set_mac_addr(qdev, set);
	if (status) {
		netif_err(qdev, ifup, qdev->ndev, "Failed to init mac address.\n");
		return status;
	}

	status = ql_route_initialize(qdev);
	if (status)
		netif_err(qdev, ifup, qdev->ndev, "Failed to init routing table.\n");

	return status;
}
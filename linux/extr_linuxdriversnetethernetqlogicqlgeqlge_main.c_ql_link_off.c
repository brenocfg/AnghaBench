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
struct ql_adapter {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ql_set_mac_addr (struct ql_adapter*,int /*<<< orphan*/ ) ; 

void ql_link_off(struct ql_adapter *qdev)
{
	netif_err(qdev, link, qdev->ndev, "Link is down.\n");
	netif_carrier_off(qdev->ndev);
	ql_set_mac_addr(qdev, 0);
}
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
struct ql_adapter {int /*<<< orphan*/  link_config; int /*<<< orphan*/  flags; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_LOOPBACK_PCS ; 
 int /*<<< orphan*/  QL_LB_LINK_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int ql_mb_set_port_cfg (struct ql_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_start_loopback(struct ql_adapter *qdev)
{
	if (netif_carrier_ok(qdev->ndev)) {
		set_bit(QL_LB_LINK_UP, &qdev->flags);
		netif_carrier_off(qdev->ndev);
	} else
		clear_bit(QL_LB_LINK_UP, &qdev->flags);
	qdev->link_config |= CFG_LOOPBACK_PCS;
	return ql_mb_set_port_cfg(qdev);
}
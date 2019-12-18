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
struct ql_adapter {int port_init; int port_link_up; int /*<<< orphan*/  ndev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ADAPTER_UP ; 
 int /*<<< orphan*/  QL_ALLMULTI ; 
 int /*<<< orphan*/  QL_PROMISCUOUS ; 
 int /*<<< orphan*/  STS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_info (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int ql_adapter_initialize (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_adapter_reset (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_alloc_rx_buffers (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_enable_all_completion_interrupts (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_enable_interrupts (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_link_on (struct ql_adapter*) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlge_restore_vlan (struct ql_adapter*) ; 
 int /*<<< orphan*/  qlge_set_multicast_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_adapter_up(struct ql_adapter *qdev)
{
	int err = 0;

	err = ql_adapter_initialize(qdev);
	if (err) {
		netif_info(qdev, ifup, qdev->ndev, "Unable to initialize adapter.\n");
		goto err_init;
	}
	set_bit(QL_ADAPTER_UP, &qdev->flags);
	ql_alloc_rx_buffers(qdev);
	/* If the port is initialized and the
	 * link is up the turn on the carrier.
	 */
	if ((ql_read32(qdev, STS) & qdev->port_init) &&
			(ql_read32(qdev, STS) & qdev->port_link_up))
		ql_link_on(qdev);
	/* Restore rx mode. */
	clear_bit(QL_ALLMULTI, &qdev->flags);
	clear_bit(QL_PROMISCUOUS, &qdev->flags);
	qlge_set_multicast_list(qdev->ndev);

	/* Restore vlan setting. */
	qlge_restore_vlan(qdev);

	ql_enable_interrupts(qdev);
	ql_enable_all_completion_interrupts(qdev);
	netif_tx_start_all_queues(qdev->ndev);

	return 0;
err_init:
	ql_adapter_reset(qdev);
	return err;
}
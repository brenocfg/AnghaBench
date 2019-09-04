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
struct e1000_ring {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  (* alloc_rx_buf ) (struct e1000_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* netdev; struct e1000_ring* rx_ring; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  e1000_configure_rx (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_configure_tx (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_desc_unused (struct e1000_ring*) ; 
 int /*<<< orphan*/  e1000_init_manageability_pt (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_restore_vlan (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_setup_rctl (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_set_rx_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  e1000e_setup_rss_hash (struct e1000_adapter*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_configure(struct e1000_adapter *adapter)
{
	struct e1000_ring *rx_ring = adapter->rx_ring;

	e1000e_set_rx_mode(adapter->netdev);

	e1000_restore_vlan(adapter);
	e1000_init_manageability_pt(adapter);

	e1000_configure_tx(adapter);

	if (adapter->netdev->features & NETIF_F_RXHASH)
		e1000e_setup_rss_hash(adapter);
	e1000_setup_rctl(adapter);
	e1000_configure_rx(adapter);
	adapter->alloc_rx_buf(rx_ring, e1000_desc_unused(rx_ring), GFP_KERNEL);
}
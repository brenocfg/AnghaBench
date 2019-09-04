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
struct igbvf_adapter {int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  igbvf_alloc_rx_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igbvf_configure_rx (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_configure_tx (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_desc_unused (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igbvf_restore_vlan (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_set_rx_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igbvf_setup_srrctl (struct igbvf_adapter*) ; 

__attribute__((used)) static void igbvf_configure(struct igbvf_adapter *adapter)
{
	igbvf_set_rx_mode(adapter->netdev);

	igbvf_restore_vlan(adapter);

	igbvf_configure_tx(adapter);
	igbvf_setup_srrctl(adapter);
	igbvf_configure_rx(adapter);
	igbvf_alloc_rx_buffers(adapter->rx_ring,
			       igbvf_desc_unused(adapter->rx_ring));
}
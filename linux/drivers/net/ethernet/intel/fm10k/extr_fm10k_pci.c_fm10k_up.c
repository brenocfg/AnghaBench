#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* update_int_moderator ) (struct fm10k_hw*) ;int /*<<< orphan*/  (* start_hw ) (struct fm10k_hw*) ;} ;
struct TYPE_4__ {int get_host_state; TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; } ;
struct fm10k_intfc {int /*<<< orphan*/  service_timer; int /*<<< orphan*/  netdev; int /*<<< orphan*/  state; struct fm10k_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  __FM10K_DOWN ; 
 int /*<<< orphan*/  __FM10K_UPDATING_STATS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_configure_rx (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_configure_tx (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_napi_enable_all (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_restore_rx_state (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*) ; 
 int /*<<< orphan*/  stub2 (struct fm10k_hw*) ; 

void fm10k_up(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;

	/* Enable Tx/Rx DMA */
	hw->mac.ops.start_hw(hw);

	/* configure Tx descriptor rings */
	fm10k_configure_tx(interface);

	/* configure Rx descriptor rings */
	fm10k_configure_rx(interface);

	/* configure interrupts */
	hw->mac.ops.update_int_moderator(hw);

	/* enable statistics capture again */
	clear_bit(__FM10K_UPDATING_STATS, interface->state);

	/* clear down bit to indicate we are ready to go */
	clear_bit(__FM10K_DOWN, interface->state);

	/* enable polling cleanups */
	fm10k_napi_enable_all(interface);

	/* re-establish Rx filters */
	fm10k_restore_rx_state(interface);

	/* enable transmits */
	netif_tx_start_all_queues(interface->netdev);

	/* kick off the service timer now */
	hw->mac.get_host_state = true;
	mod_timer(&interface->service_timer, jiffies);
}
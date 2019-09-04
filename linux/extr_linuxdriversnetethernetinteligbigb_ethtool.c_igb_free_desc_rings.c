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
struct igb_adapter {int /*<<< orphan*/  test_rx_ring; int /*<<< orphan*/  test_tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  igb_free_rx_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_free_tx_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igb_free_desc_rings(struct igb_adapter *adapter)
{
	igb_free_tx_resources(&adapter->test_tx_ring);
	igb_free_rx_resources(&adapter->test_rx_ring);
}
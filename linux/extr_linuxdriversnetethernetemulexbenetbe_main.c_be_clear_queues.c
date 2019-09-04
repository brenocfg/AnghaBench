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
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_evt_queues_destroy (struct be_adapter*) ; 
 int /*<<< orphan*/  be_mcc_queues_destroy (struct be_adapter*) ; 
 int /*<<< orphan*/  be_rx_cqs_destroy (struct be_adapter*) ; 
 int /*<<< orphan*/  be_tx_queues_destroy (struct be_adapter*) ; 

__attribute__((used)) static void be_clear_queues(struct be_adapter *adapter)
{
	be_mcc_queues_destroy(adapter);
	be_rx_cqs_destroy(adapter);
	be_tx_queues_destroy(adapter);
	be_evt_queues_destroy(adapter);
}
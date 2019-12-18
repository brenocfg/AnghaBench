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
struct ena_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ena_destroy_all_rx_queues (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_destroy_all_tx_queues (struct ena_adapter*) ; 

__attribute__((used)) static void ena_destroy_all_io_queues(struct ena_adapter *adapter)
{
	ena_destroy_all_tx_queues(adapter);
	ena_destroy_all_rx_queues(adapter);
}
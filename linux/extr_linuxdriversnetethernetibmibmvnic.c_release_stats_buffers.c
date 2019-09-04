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
struct ibmvnic_adapter {int /*<<< orphan*/ * rx_stats_buffers; int /*<<< orphan*/ * tx_stats_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_stats_buffers(struct ibmvnic_adapter *adapter)
{
	kfree(adapter->tx_stats_buffers);
	kfree(adapter->rx_stats_buffers);
	adapter->tx_stats_buffers = NULL;
	adapter->rx_stats_buffers = NULL;
}
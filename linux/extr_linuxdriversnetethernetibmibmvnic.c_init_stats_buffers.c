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
struct ibmvnic_tx_queue_stats {int dummy; } ;
struct ibmvnic_rx_queue_stats {int dummy; } ;
struct ibmvnic_adapter {void* rx_stats_buffers; void* tx_stats_buffers; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IBMVNIC_MAX_QUEUES ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_stats_buffers(struct ibmvnic_adapter *adapter)
{
	adapter->tx_stats_buffers =
				kcalloc(IBMVNIC_MAX_QUEUES,
					sizeof(struct ibmvnic_tx_queue_stats),
					GFP_KERNEL);
	if (!adapter->tx_stats_buffers)
		return -ENOMEM;

	adapter->rx_stats_buffers =
				kcalloc(IBMVNIC_MAX_QUEUES,
					sizeof(struct ibmvnic_rx_queue_stats),
					GFP_KERNEL);
	if (!adapter->rx_stats_buffers)
		return -ENOMEM;

	return 0;
}
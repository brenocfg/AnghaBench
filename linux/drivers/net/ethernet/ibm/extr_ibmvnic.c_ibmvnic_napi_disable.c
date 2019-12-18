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
struct ibmvnic_adapter {int napi_enabled; int req_rx_queues; int /*<<< orphan*/ * napi; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ibmvnic_napi_disable(struct ibmvnic_adapter *adapter)
{
	int i;

	if (!adapter->napi_enabled)
		return;

	for (i = 0; i < adapter->req_rx_queues; i++) {
		netdev_dbg(adapter->netdev, "Disabling napi[%d]\n", i);
		napi_disable(&adapter->napi[i]);
	}

	adapter->napi_enabled = false;
}
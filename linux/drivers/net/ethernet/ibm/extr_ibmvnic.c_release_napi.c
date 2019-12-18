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
struct ibmvnic_adapter {int num_active_rx_napi; int napi_enabled; int /*<<< orphan*/ * napi; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_napi(struct ibmvnic_adapter *adapter)
{
	int i;

	if (!adapter->napi)
		return;

	for (i = 0; i < adapter->num_active_rx_napi; i++) {
		netdev_dbg(adapter->netdev, "Releasing napi[%d]\n", i);
		netif_napi_del(&adapter->napi[i]);
	}

	kfree(adapter->napi);
	adapter->napi = NULL;
	adapter->num_active_rx_napi = 0;
	adapter->napi_enabled = false;
}
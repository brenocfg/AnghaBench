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
struct napi_struct {int dummy; } ;
struct ibmvnic_adapter {int req_rx_queues; int num_active_rx_napi; int /*<<< orphan*/ * napi; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  ibmvnic_poll ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_napi(struct ibmvnic_adapter *adapter)
{
	int i;

	adapter->napi = kcalloc(adapter->req_rx_queues,
				sizeof(struct napi_struct), GFP_KERNEL);
	if (!adapter->napi)
		return -ENOMEM;

	for (i = 0; i < adapter->req_rx_queues; i++) {
		netdev_dbg(adapter->netdev, "Adding napi[%d]\n", i);
		netif_napi_add(adapter->netdev, &adapter->napi[i],
			       ibmvnic_poll, NAPI_POLL_WEIGHT);
	}

	adapter->num_active_rx_napi = adapter->req_rx_queues;
	return 0;
}
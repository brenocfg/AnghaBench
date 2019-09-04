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
struct ibmvnic_adapter {int napi_enabled; int req_rx_queues; int /*<<< orphan*/ * napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvnic_napi_enable(struct ibmvnic_adapter *adapter)
{
	int i;

	if (adapter->napi_enabled)
		return;

	for (i = 0; i < adapter->req_rx_queues; i++)
		napi_enable(&adapter->napi[i]);

	adapter->napi_enabled = true;
}
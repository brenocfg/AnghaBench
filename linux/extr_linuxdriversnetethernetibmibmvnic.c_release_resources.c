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
struct ibmvnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_login_rsp_buffer (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_napi (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_rx_pools (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_tx_pools (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_vpd_data (struct ibmvnic_adapter*) ; 

__attribute__((used)) static void release_resources(struct ibmvnic_adapter *adapter)
{
	release_vpd_data(adapter);

	release_tx_pools(adapter);
	release_rx_pools(adapter);

	release_napi(adapter);
	release_login_rsp_buffer(adapter);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ibmvnic_adapter {int /*<<< orphan*/ * tx_pool; int /*<<< orphan*/ * tso_pool; TYPE_1__* login_rsp_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_txsubm_subcrqs; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int reset_one_tx_pool (struct ibmvnic_adapter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reset_tx_pools(struct ibmvnic_adapter *adapter)
{
	int tx_scrqs;
	int i, rc;

	tx_scrqs = be32_to_cpu(adapter->login_rsp_buf->num_txsubm_subcrqs);
	for (i = 0; i < tx_scrqs; i++) {
		rc = reset_one_tx_pool(adapter, &adapter->tso_pool[i]);
		if (rc)
			return rc;
		rc = reset_one_tx_pool(adapter, &adapter->tx_pool[i]);
		if (rc)
			return rc;
	}

	return 0;
}
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
struct ibmvnic_tx_pool {int num_buffers; int* free_map; scalar_t__ producer_index; scalar_t__ consumer_index; int /*<<< orphan*/  tx_buff; int /*<<< orphan*/  long_term_buff; } ;
struct ibmvnic_tx_buff {int dummy; } ;
struct ibmvnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int reset_long_term_buff (struct ibmvnic_adapter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reset_one_tx_pool(struct ibmvnic_adapter *adapter,
			     struct ibmvnic_tx_pool *tx_pool)
{
	int rc, i;

	rc = reset_long_term_buff(adapter, &tx_pool->long_term_buff);
	if (rc)
		return rc;

	memset(tx_pool->tx_buff, 0,
	       tx_pool->num_buffers *
	       sizeof(struct ibmvnic_tx_buff));

	for (i = 0; i < tx_pool->num_buffers; i++)
		tx_pool->free_map[i] = i;

	tx_pool->consumer_index = 0;
	tx_pool->producer_index = 0;

	return 0;
}
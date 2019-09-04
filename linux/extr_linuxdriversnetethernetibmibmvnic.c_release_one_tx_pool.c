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
struct ibmvnic_tx_pool {int /*<<< orphan*/  long_term_buff; int /*<<< orphan*/  free_map; int /*<<< orphan*/  tx_buff; } ;
struct ibmvnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_long_term_buff (struct ibmvnic_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_one_tx_pool(struct ibmvnic_adapter *adapter,
				struct ibmvnic_tx_pool *tx_pool)
{
	kfree(tx_pool->tx_buff);
	kfree(tx_pool->free_map);
	free_long_term_buff(adapter, &tx_pool->long_term_buff);
}
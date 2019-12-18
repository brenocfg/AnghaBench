#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ibmvnic_rx_pool {int size; int index; int buff_size; int active; int* free_map; scalar_t__ next_free; scalar_t__ next_alloc; int /*<<< orphan*/  available; int /*<<< orphan*/  long_term_buff; void* rx_buff; } ;
struct ibmvnic_rx_buff {int dummy; } ;
struct ibmvnic_adapter {int num_active_rx_pools; int req_rx_add_entries_per_subcrq; int /*<<< orphan*/  netdev; struct ibmvnic_rx_pool* rx_pool; TYPE_2__* login_rsp_buf; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  off_rxadd_buff_size; int /*<<< orphan*/  num_rxadd_subcrqs; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ alloc_long_term_buff (struct ibmvnic_adapter*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_rx_pools (struct ibmvnic_adapter*) ; 

__attribute__((used)) static int init_rx_pools(struct net_device *netdev)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	struct device *dev = &adapter->vdev->dev;
	struct ibmvnic_rx_pool *rx_pool;
	int rxadd_subcrqs;
	u64 *size_array;
	int i, j;

	rxadd_subcrqs =
		be32_to_cpu(adapter->login_rsp_buf->num_rxadd_subcrqs);
	size_array = (u64 *)((u8 *)(adapter->login_rsp_buf) +
		be32_to_cpu(adapter->login_rsp_buf->off_rxadd_buff_size));

	adapter->rx_pool = kcalloc(rxadd_subcrqs,
				   sizeof(struct ibmvnic_rx_pool),
				   GFP_KERNEL);
	if (!adapter->rx_pool) {
		dev_err(dev, "Failed to allocate rx pools\n");
		return -1;
	}

	adapter->num_active_rx_pools = rxadd_subcrqs;

	for (i = 0; i < rxadd_subcrqs; i++) {
		rx_pool = &adapter->rx_pool[i];

		netdev_dbg(adapter->netdev,
			   "Initializing rx_pool[%d], %lld buffs, %lld bytes each\n",
			   i, adapter->req_rx_add_entries_per_subcrq,
			   be64_to_cpu(size_array[i]));

		rx_pool->size = adapter->req_rx_add_entries_per_subcrq;
		rx_pool->index = i;
		rx_pool->buff_size = be64_to_cpu(size_array[i]);
		rx_pool->active = 1;

		rx_pool->free_map = kcalloc(rx_pool->size, sizeof(int),
					    GFP_KERNEL);
		if (!rx_pool->free_map) {
			release_rx_pools(adapter);
			return -1;
		}

		rx_pool->rx_buff = kcalloc(rx_pool->size,
					   sizeof(struct ibmvnic_rx_buff),
					   GFP_KERNEL);
		if (!rx_pool->rx_buff) {
			dev_err(dev, "Couldn't alloc rx buffers\n");
			release_rx_pools(adapter);
			return -1;
		}

		if (alloc_long_term_buff(adapter, &rx_pool->long_term_buff,
					 rx_pool->size * rx_pool->buff_size)) {
			release_rx_pools(adapter);
			return -1;
		}

		for (j = 0; j < rx_pool->size; ++j)
			rx_pool->free_map[j] = j;

		atomic_set(&rx_pool->available, 0);
		rx_pool->next_alloc = 0;
		rx_pool->next_free = 0;
	}

	return 0;
}
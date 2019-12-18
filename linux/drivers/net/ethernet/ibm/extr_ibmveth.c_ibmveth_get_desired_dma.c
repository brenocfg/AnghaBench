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
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int mtu; } ;
struct iommu_table {int dummy; } ;
struct ibmveth_rx_q_entry {int dummy; } ;
struct ibmveth_adapter {TYPE_1__* rx_buff_pool; } ;
struct TYPE_2__ {unsigned long size; int buff_size; scalar_t__ active; } ;

/* Variables and functions */
 unsigned long IBMVETH_BUFF_LIST_SIZE ; 
 unsigned long IBMVETH_FILT_LIST_SIZE ; 
 int IBMVETH_IO_ENTITLEMENT_DEFAULT ; 
 int IBMVETH_NUM_BUFF_POOLS ; 
 unsigned long IOMMU_PAGE_ALIGN (int,struct iommu_table*) ; 
 struct net_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct iommu_table* get_iommu_table_base (int /*<<< orphan*/ *) ; 
 struct ibmveth_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static unsigned long ibmveth_get_desired_dma(struct vio_dev *vdev)
{
	struct net_device *netdev = dev_get_drvdata(&vdev->dev);
	struct ibmveth_adapter *adapter;
	struct iommu_table *tbl;
	unsigned long ret;
	int i;
	int rxqentries = 1;

	tbl = get_iommu_table_base(&vdev->dev);

	/* netdev inits at probe time along with the structures we need below*/
	if (netdev == NULL)
		return IOMMU_PAGE_ALIGN(IBMVETH_IO_ENTITLEMENT_DEFAULT, tbl);

	adapter = netdev_priv(netdev);

	ret = IBMVETH_BUFF_LIST_SIZE + IBMVETH_FILT_LIST_SIZE;
	ret += IOMMU_PAGE_ALIGN(netdev->mtu, tbl);

	for (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++) {
		/* add the size of the active receive buffers */
		if (adapter->rx_buff_pool[i].active)
			ret +=
			    adapter->rx_buff_pool[i].size *
			    IOMMU_PAGE_ALIGN(adapter->rx_buff_pool[i].
					     buff_size, tbl);
		rxqentries += adapter->rx_buff_pool[i].size;
	}
	/* add the size of the receive queue entries */
	ret += IOMMU_PAGE_ALIGN(
		rxqentries * sizeof(struct ibmveth_rx_q_entry), tbl);

	return ret;
}
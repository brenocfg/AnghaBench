#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long code; } ;
struct TYPE_6__ {int /*<<< orphan*/  free_pages; int /*<<< orphan*/  tot_pages; int /*<<< orphan*/  page_size; TYPE_2__ rc; } ;
union ibmvnic_crq {TYPE_3__ query_map_rsp; } ;
struct net_device {int dummy; } ;
struct ibmvnic_adapter {TYPE_1__* vdev; struct net_device* netdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,long) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_query_map_rsp(union ibmvnic_crq *crq,
				 struct ibmvnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct device *dev = &adapter->vdev->dev;
	long rc;

	rc = crq->query_map_rsp.rc.code;
	if (rc) {
		dev_err(dev, "Error %ld in QUERY_MAP_RSP\n", rc);
		return;
	}
	netdev_dbg(netdev, "page_size = %d\ntot_pages = %d\nfree_pages = %d\n",
		   crq->query_map_rsp.page_size, crq->query_map_rsp.tot_pages,
		   crq->query_map_rsp.free_pages);
}
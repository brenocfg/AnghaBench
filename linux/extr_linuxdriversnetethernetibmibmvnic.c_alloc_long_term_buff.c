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
struct ibmvnic_long_term_buff {int size; int /*<<< orphan*/  addr; int /*<<< orphan*/  buff; int /*<<< orphan*/  map_id; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  fw_done_rc; int /*<<< orphan*/  fw_done; int /*<<< orphan*/  map_id; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int send_request_map (struct ibmvnic_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_long_term_buff(struct ibmvnic_adapter *adapter,
				struct ibmvnic_long_term_buff *ltb, int size)
{
	struct device *dev = &adapter->vdev->dev;
	int rc;

	ltb->size = size;
	ltb->buff = dma_alloc_coherent(dev, ltb->size, &ltb->addr,
				       GFP_KERNEL);

	if (!ltb->buff) {
		dev_err(dev, "Couldn't alloc long term buffer\n");
		return -ENOMEM;
	}
	ltb->map_id = adapter->map_id;
	adapter->map_id++;

	init_completion(&adapter->fw_done);
	rc = send_request_map(adapter, ltb->addr,
			      ltb->size, ltb->map_id);
	if (rc) {
		dma_free_coherent(dev, ltb->size, ltb->buff, ltb->addr);
		return rc;
	}
	wait_for_completion(&adapter->fw_done);

	if (adapter->fw_done_rc) {
		dev_err(dev, "Couldn't map long term buffer,rc = %d\n",
			adapter->fw_done_rc);
		dma_free_coherent(dev, ltb->size, ltb->buff, ltb->addr);
		return -1;
	}
	return 0;
}
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
struct virtchnl_vsi_resource {scalar_t__ num_queue_pairs; } ;
struct iavf_adapter {TYPE_2__* vf_res; TYPE_1__* pdev; } ;
struct TYPE_4__ {scalar_t__ num_queue_pairs; int num_vsis; struct virtchnl_vsi_resource* vsi_res; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IAVF_MAX_REQ_QUEUES ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 

__attribute__((used)) static void iavf_validate_num_queues(struct iavf_adapter *adapter)
{
	if (adapter->vf_res->num_queue_pairs > IAVF_MAX_REQ_QUEUES) {
		struct virtchnl_vsi_resource *vsi_res;
		int i;

		dev_info(&adapter->pdev->dev, "Received %d queues, but can only have a max of %d\n",
			 adapter->vf_res->num_queue_pairs,
			 IAVF_MAX_REQ_QUEUES);
		dev_info(&adapter->pdev->dev, "Fixing by reducing queues to %d\n",
			 IAVF_MAX_REQ_QUEUES);
		adapter->vf_res->num_queue_pairs = IAVF_MAX_REQ_QUEUES;
		for (i = 0; i < adapter->vf_res->num_vsis; i++) {
			vsi_res = &adapter->vf_res->vsi_res[i];
			vsi_res->num_queue_pairs = IAVF_MAX_REQ_QUEUES;
		}
	}
}
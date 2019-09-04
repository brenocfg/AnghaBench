#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  code; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; TYPE_3__ rc; } ;
union ibmvnic_crq {TYPE_4__ get_vpd_size_rsp; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  fw_done; TYPE_1__* vpd; TYPE_2__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_vpd_size_rsp(union ibmvnic_crq *crq,
				struct ibmvnic_adapter *adapter)
{
	struct device *dev = &adapter->vdev->dev;

	if (crq->get_vpd_size_rsp.rc.code) {
		dev_err(dev, "Error retrieving VPD size, rc=%x\n",
			crq->get_vpd_size_rsp.rc.code);
		complete(&adapter->fw_done);
		return;
	}

	adapter->vpd->len = be64_to_cpu(crq->get_vpd_size_rsp.len);
	complete(&adapter->fw_done);
}
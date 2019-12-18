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
struct pci_device_id {int dummy; } ;
struct TYPE_5__ {void* instance_state; } ;
struct hnae3_handle {TYPE_2__ rinfo; TYPE_3__* pdev; TYPE_1__* ae_algo; } ;
struct hnae3_ae_ops {scalar_t__ (* get_hw_reset_stat ) (struct hnae3_handle*) ;scalar_t__ (* ae_dev_resetting ) (struct hnae3_handle*) ;} ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; } ;
struct TYPE_4__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
 int EBUSY ; 
 void* HNS_ROCE_STATE_INIT ; 
 void* HNS_ROCE_STATE_INITED ; 
 void* HNS_ROCE_STATE_NON_INIT ; 
 int __hns_roce_hw_v2_init_instance (struct hnae3_handle*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  hns_roce_hw_v2_pci_tbl ; 
 struct pci_device_id* pci_match_id (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ stub1 (struct hnae3_handle*) ; 
 scalar_t__ stub2 (struct hnae3_handle*) ; 
 scalar_t__ stub3 (struct hnae3_handle*) ; 
 scalar_t__ stub4 (struct hnae3_handle*) ; 

__attribute__((used)) static int hns_roce_hw_v2_init_instance(struct hnae3_handle *handle)
{
	const struct hnae3_ae_ops *ops = handle->ae_algo->ops;
	const struct pci_device_id *id;
	struct device *dev = &handle->pdev->dev;
	int ret;

	handle->rinfo.instance_state = HNS_ROCE_STATE_INIT;

	if (ops->ae_dev_resetting(handle) || ops->get_hw_reset_stat(handle)) {
		handle->rinfo.instance_state = HNS_ROCE_STATE_NON_INIT;
		goto reset_chk_err;
	}

	id = pci_match_id(hns_roce_hw_v2_pci_tbl, handle->pdev);
	if (!id)
		return 0;

	ret = __hns_roce_hw_v2_init_instance(handle);
	if (ret) {
		handle->rinfo.instance_state = HNS_ROCE_STATE_NON_INIT;
		dev_err(dev, "RoCE instance init failed! ret = %d\n", ret);
		if (ops->ae_dev_resetting(handle) ||
		    ops->get_hw_reset_stat(handle))
			goto reset_chk_err;
		else
			return ret;
	}

	handle->rinfo.instance_state = HNS_ROCE_STATE_INITED;


	return 0;

reset_chk_err:
	dev_err(dev, "Device is busy in resetting state.\n"
		     "please retry later.\n");

	return -EBUSY;
}
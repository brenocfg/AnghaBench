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
struct qlcnic_dcb_mbx_params {int dummy; } ;
struct qlcnic_dcb_cfg {int dummy; } ;
struct qlcnic_dcb {int /*<<< orphan*/ * wq; int /*<<< orphan*/ * cfg; void* param; TYPE_2__* adapter; int /*<<< orphan*/  aen_work; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_dcb_aen_work ; 

__attribute__((used)) static int __qlcnic_dcb_attach(struct qlcnic_dcb *dcb)
{
	int err = 0;

	INIT_DELAYED_WORK(&dcb->aen_work, qlcnic_dcb_aen_work);

	dcb->wq = create_singlethread_workqueue("qlcnic-dcb");
	if (!dcb->wq) {
		dev_err(&dcb->adapter->pdev->dev,
			"DCB workqueue allocation failed. DCB will be disabled\n");
		return -1;
	}

	dcb->cfg = kzalloc(sizeof(struct qlcnic_dcb_cfg), GFP_ATOMIC);
	if (!dcb->cfg) {
		err = -ENOMEM;
		goto out_free_wq;
	}

	dcb->param = kzalloc(sizeof(struct qlcnic_dcb_mbx_params), GFP_ATOMIC);
	if (!dcb->param) {
		err = -ENOMEM;
		goto out_free_cfg;
	}

	return 0;
out_free_cfg:
	kfree(dcb->cfg);
	dcb->cfg = NULL;

out_free_wq:
	destroy_workqueue(dcb->wq);
	dcb->wq = NULL;

	return err;
}
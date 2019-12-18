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
struct i40iw_sc_dev {int /*<<< orphan*/  ccq; TYPE_1__* ccq_ops; int /*<<< orphan*/  hw; scalar_t__ is_pf; void* back_dev; } ;
struct i40iw_device {int iw_status; int /*<<< orphan*/  init_state; int /*<<< orphan*/ * param_wq; void* virtchnl_wq; int /*<<< orphan*/  pble_rsrc; struct i40iw_sc_dev sc_dev; int /*<<< orphan*/  pbl_mutex; struct i40e_client* client; int /*<<< orphan*/ * ldev; struct i40iw_handler* hdl; } ;
struct i40iw_handler {int /*<<< orphan*/  ldev; struct i40iw_device device; } ;
struct i40e_info {int /*<<< orphan*/  netdev; } ;
struct i40e_client {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {int /*<<< orphan*/  (* ccq_arm ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AEQ_CREATED ; 
 int /*<<< orphan*/  CCQ_CREATED ; 
 int /*<<< orphan*/  CEQ_CREATED ; 
 int /*<<< orphan*/  CQP_CREATED ; 
 int ENOMEM ; 
 int ERESTART ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEQ_CREATED ; 
 int /*<<< orphan*/  ILQ_CREATED ; 
 int /*<<< orphan*/  INITIAL_STATE ; 
 int /*<<< orphan*/  IP_ADDR_REGISTERED ; 
 int /*<<< orphan*/  PBLE_CHUNK_MEM ; 
 int /*<<< orphan*/  RDMA_DEV_REGISTERED ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 void* alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_add_handler (struct i40iw_handler*) ; 
 int i40iw_add_mac_ip (struct i40iw_device*) ; 
 int i40iw_create_ccq (struct i40iw_device*) ; 
 int i40iw_create_cqp (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_deinit_device (struct i40iw_device*) ; 
 struct i40iw_handler* i40iw_find_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_get_used_rsrc (struct i40iw_device*) ; 
 int i40iw_hmc_init_pble (struct i40iw_sc_dev*,int /*<<< orphan*/ ) ; 
 int i40iw_hmc_setup (struct i40iw_device*) ; 
 int i40iw_initialize_hw_resources (struct i40iw_device*) ; 
 int i40iw_initialize_ieq (struct i40iw_device*) ; 
 int i40iw_initialize_ilq (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_port_ibevent (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,...) ; 
 int /*<<< orphan*/  i40iw_pr_info (char*) ; 
 scalar_t__ i40iw_register_rdma_device (struct i40iw_device*) ; 
 int i40iw_setup_aeq (struct i40iw_device*) ; 
 int i40iw_setup_ceqs (struct i40iw_device*,struct i40e_info*) ; 
 scalar_t__ i40iw_setup_cm_core (struct i40iw_device*) ; 
 int i40iw_setup_init_state (struct i40iw_handler*,struct i40e_info*,struct i40e_client*) ; 
 int /*<<< orphan*/  i40iw_wait_pe_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i40iw_handler*) ; 
 struct i40iw_handler* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40iw_open(struct i40e_info *ldev, struct i40e_client *client)
{
	struct i40iw_device *iwdev;
	struct i40iw_sc_dev *dev;
	enum i40iw_status_code status;
	struct i40iw_handler *hdl;

	hdl = i40iw_find_netdev(ldev->netdev);
	if (hdl)
		return 0;

	hdl = kzalloc(sizeof(*hdl), GFP_KERNEL);
	if (!hdl)
		return -ENOMEM;
	iwdev = &hdl->device;
	iwdev->hdl = hdl;
	dev = &iwdev->sc_dev;
	if (i40iw_setup_cm_core(iwdev)) {
		kfree(iwdev->hdl);
		return -ENOMEM;
	}

	dev->back_dev = (void *)iwdev;
	iwdev->ldev = &hdl->ldev;
	iwdev->client = client;
	mutex_init(&iwdev->pbl_mutex);
	i40iw_add_handler(hdl);

	do {
		status = i40iw_setup_init_state(hdl, ldev, client);
		if (status)
			break;
		iwdev->init_state = INITIAL_STATE;
		if (dev->is_pf)
			i40iw_wait_pe_ready(dev->hw);
		status = i40iw_create_cqp(iwdev);
		if (status)
			break;
		iwdev->init_state = CQP_CREATED;
		status = i40iw_hmc_setup(iwdev);
		if (status)
			break;
		status = i40iw_create_ccq(iwdev);
		if (status)
			break;
		iwdev->init_state = CCQ_CREATED;
		status = i40iw_initialize_ilq(iwdev);
		if (status)
			break;
		iwdev->init_state = ILQ_CREATED;
		status = i40iw_initialize_ieq(iwdev);
		if (status)
			break;
		iwdev->init_state = IEQ_CREATED;
		status = i40iw_setup_aeq(iwdev);
		if (status)
			break;
		iwdev->init_state = AEQ_CREATED;
		status = i40iw_setup_ceqs(iwdev, ldev);
		if (status)
			break;
		iwdev->init_state = CEQ_CREATED;
		status = i40iw_initialize_hw_resources(iwdev);
		if (status)
			break;
		i40iw_get_used_rsrc(iwdev);
		dev->ccq_ops->ccq_arm(dev->ccq);
		status = i40iw_hmc_init_pble(&iwdev->sc_dev, iwdev->pble_rsrc);
		if (status)
			break;
		iwdev->init_state = PBLE_CHUNK_MEM;
		iwdev->virtchnl_wq = alloc_ordered_workqueue("iwvch", WQ_MEM_RECLAIM);
		status = i40iw_add_mac_ip(iwdev);
		if (status)
			break;
		iwdev->init_state = IP_ADDR_REGISTERED;
		if (i40iw_register_rdma_device(iwdev)) {
			i40iw_pr_err("register rdma device fail\n");
			break;
		};

		iwdev->init_state = RDMA_DEV_REGISTERED;
		iwdev->iw_status = 1;
		i40iw_port_ibevent(iwdev);
		iwdev->param_wq = alloc_ordered_workqueue("l2params", WQ_MEM_RECLAIM);
		if(iwdev->param_wq == NULL)
			break;
		i40iw_pr_info("i40iw_open completed\n");
		return 0;
	} while (0);

	i40iw_pr_err("status = %d last completion = %d\n", status, iwdev->init_state);
	i40iw_deinit_device(iwdev);
	return -ERESTART;
}
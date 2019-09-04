#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct i40iw_sc_dev {int /*<<< orphan*/  hmc_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  pestat; } ;
struct i40iw_device {int init_state; int /*<<< orphan*/  hdl; TYPE_1__ vsi; int /*<<< orphan*/  cm_core; int /*<<< orphan*/  reset; int /*<<< orphan*/  pble_rsrc; int /*<<< orphan*/  mac_ip_table_idx; int /*<<< orphan*/  iwibdev; int /*<<< orphan*/  iw_status; scalar_t__ param_wq; struct i40iw_sc_dev sc_dev; struct i40e_info* ldev; } ;
struct i40e_info {int dummy; } ;

/* Variables and functions */
#define  AEQ_CREATED 139 
#define  CCQ_CREATED 138 
#define  CEQ_CREATED 137 
#define  CQP_CREATED 136 
#define  HMC_OBJS_CREATED 135 
 int /*<<< orphan*/  I40IW_PUDA_RSRC_TYPE_IEQ ; 
 int /*<<< orphan*/  I40IW_PUDA_RSRC_TYPE_ILQ ; 
#define  IEQ_CREATED 134 
#define  ILQ_CREATED 133 
#define  INITIAL_STATE 132 
#define  INVALID_STATE 131 
#define  IP_ADDR_REGISTERED 130 
#define  PBLE_CHUNK_MEM 129 
#define  RDMA_DEV_REGISTERED 128 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  i40iw_cleanup_cm_core (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_del_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_del_hmc_objects (struct i40iw_sc_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_del_init_mem (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_del_macip_entry (struct i40iw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_dele_ceqs (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_destroy_aeq (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_destroy_ccq (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_destroy_cqp (struct i40iw_device*,int) ; 
 int /*<<< orphan*/  i40iw_destroy_pble_pool (struct i40iw_sc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_destroy_rdma_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_find_i40e_handler (struct i40e_info*) ; 
 int /*<<< orphan*/  i40iw_port_ibevent (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,int) ; 
 int /*<<< orphan*/  i40iw_pr_info (char*,int) ; 
 int /*<<< orphan*/  i40iw_puda_dele_resources (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_vsi_stats_free (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_deinit_device(struct i40iw_device *iwdev)
{
	struct i40e_info *ldev = iwdev->ldev;

	struct i40iw_sc_dev *dev = &iwdev->sc_dev;

	i40iw_pr_info("state = %d\n", iwdev->init_state);
	if (iwdev->param_wq)
		destroy_workqueue(iwdev->param_wq);

	switch (iwdev->init_state) {
	case RDMA_DEV_REGISTERED:
		iwdev->iw_status = 0;
		i40iw_port_ibevent(iwdev);
		i40iw_destroy_rdma_device(iwdev->iwibdev);
		/* fallthrough */
	case IP_ADDR_REGISTERED:
		if (!iwdev->reset)
			i40iw_del_macip_entry(iwdev, (u8)iwdev->mac_ip_table_idx);
		/* fallthrough */
		/* fallthrough */
	case PBLE_CHUNK_MEM:
		i40iw_destroy_pble_pool(dev, iwdev->pble_rsrc);
		/* fallthrough */
	case CEQ_CREATED:
		i40iw_dele_ceqs(iwdev);
		/* fallthrough */
	case AEQ_CREATED:
		i40iw_destroy_aeq(iwdev);
		/* fallthrough */
	case IEQ_CREATED:
		i40iw_puda_dele_resources(&iwdev->vsi, I40IW_PUDA_RSRC_TYPE_IEQ, iwdev->reset);
		/* fallthrough */
	case ILQ_CREATED:
		i40iw_puda_dele_resources(&iwdev->vsi, I40IW_PUDA_RSRC_TYPE_ILQ, iwdev->reset);
		/* fallthrough */
	case CCQ_CREATED:
		i40iw_destroy_ccq(iwdev);
		/* fallthrough */
	case HMC_OBJS_CREATED:
		i40iw_del_hmc_objects(dev, dev->hmc_info, true, iwdev->reset);
		/* fallthrough */
	case CQP_CREATED:
		i40iw_destroy_cqp(iwdev, true);
		/* fallthrough */
	case INITIAL_STATE:
		i40iw_cleanup_cm_core(&iwdev->cm_core);
		if (iwdev->vsi.pestat) {
			i40iw_vsi_stats_free(&iwdev->vsi);
			kfree(iwdev->vsi.pestat);
		}
		i40iw_del_init_mem(iwdev);
		break;
	case INVALID_STATE:
		/* fallthrough */
	default:
		i40iw_pr_err("bad init_state = %d\n", iwdev->init_state);
		break;
	}

	i40iw_del_handler(i40iw_find_i40e_handler(ldev));
	kfree(iwdev->hdl);
}
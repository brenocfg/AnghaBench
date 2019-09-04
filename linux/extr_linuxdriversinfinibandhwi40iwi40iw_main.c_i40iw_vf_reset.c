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
typedef  scalar_t__ u32 ;
struct i40iw_virt_mem {int size; struct i40iw_vfdev* va; } ;
struct i40iw_vfdev {scalar_t__ vf_id; int /*<<< orphan*/  iw_vf_idx; int /*<<< orphan*/  hmc_info; } ;
struct i40iw_sc_dev {int /*<<< orphan*/  hw; struct i40iw_vfdev** vf_dev; scalar_t__ back_dev; } ;
struct i40iw_hmc_obj_info {int dummy; } ;
struct i40iw_hmc_fcn_info {int free_fcn; int /*<<< orphan*/  iw_vf_idx; scalar_t__ vf_id; } ;
struct TYPE_4__ {struct i40iw_sc_dev sc_dev; } ;
struct i40iw_handler {TYPE_1__ device; } ;
struct TYPE_6__ {TYPE_2__* pestat; } ;
struct i40iw_device {TYPE_3__ vsi; } ;
struct i40e_info {int dummy; } ;
struct i40e_client {int dummy; } ;
typedef  int /*<<< orphan*/  hmc_fcn_info ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int I40IW_HMC_IW_MAX ; 
 unsigned int I40IW_MAX_PE_ENABLED_VF_COUNT ; 
 int /*<<< orphan*/  i40iw_cqp_manage_hmc_fcn_cmd (struct i40iw_sc_dev*,struct i40iw_hmc_fcn_info*) ; 
 int /*<<< orphan*/  i40iw_del_hmc_objects (struct i40iw_sc_dev*,int /*<<< orphan*/ *,int,int) ; 
 struct i40iw_handler* i40iw_find_i40e_handler (struct i40e_info*) ; 
 int /*<<< orphan*/  i40iw_free_virt_mem (int /*<<< orphan*/ ,struct i40iw_virt_mem*) ; 
 int /*<<< orphan*/  memset (struct i40iw_hmc_fcn_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void i40iw_vf_reset(struct i40e_info *ldev, struct i40e_client *client, u32 vf_id)
{
	struct i40iw_handler *hdl;
	struct i40iw_sc_dev *dev;
	struct i40iw_hmc_fcn_info hmc_fcn_info;
	struct i40iw_virt_mem vf_dev_mem;
	struct i40iw_vfdev *tmp_vfdev;
	unsigned int i;
	unsigned long flags;
	struct i40iw_device *iwdev;

	hdl = i40iw_find_i40e_handler(ldev);
	if (!hdl)
		return;

	dev = &hdl->device.sc_dev;
	iwdev = (struct i40iw_device *)dev->back_dev;

	for (i = 0; i < I40IW_MAX_PE_ENABLED_VF_COUNT; i++) {
		if (!dev->vf_dev[i] || (dev->vf_dev[i]->vf_id != vf_id))
			continue;
		/* free all resources allocated on behalf of vf */
		tmp_vfdev = dev->vf_dev[i];
		spin_lock_irqsave(&iwdev->vsi.pestat->lock, flags);
		dev->vf_dev[i] = NULL;
		spin_unlock_irqrestore(&iwdev->vsi.pestat->lock, flags);
		i40iw_del_hmc_objects(dev, &tmp_vfdev->hmc_info, false, false);
		/* remove vf hmc function */
		memset(&hmc_fcn_info, 0, sizeof(hmc_fcn_info));
		hmc_fcn_info.vf_id = vf_id;
		hmc_fcn_info.iw_vf_idx = tmp_vfdev->iw_vf_idx;
		hmc_fcn_info.free_fcn = true;
		i40iw_cqp_manage_hmc_fcn_cmd(dev, &hmc_fcn_info);
		/* free vf_dev */
		vf_dev_mem.va = tmp_vfdev;
		vf_dev_mem.size = sizeof(struct i40iw_vfdev) +
					sizeof(struct i40iw_hmc_obj_info) * I40IW_HMC_IW_MAX;
		i40iw_free_virt_mem(dev->hw, &vf_dev_mem);
		break;
	}
}
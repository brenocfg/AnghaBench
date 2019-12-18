#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvmet_fc_target_port {int port_num; int /*<<< orphan*/  port_id; struct nvmet_fc_tgtport* private; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct nvmet_fc_tgtport {struct nvmet_fc_target_port fc_target_port; int /*<<< orphan*/  tgt_list; scalar_t__ max_sg_cnt; int /*<<< orphan*/  assoc_cnt; int /*<<< orphan*/  ref; int /*<<< orphan*/  assoc_list; int /*<<< orphan*/  ls_busylist; int /*<<< orphan*/  ls_list; int /*<<< orphan*/  lock; struct nvmet_fc_target_template* ops; struct device* dev; } ;
struct nvmet_fc_target_template {scalar_t__ max_sgl_segments; scalar_t__ target_priv_sz; int /*<<< orphan*/  dma_boundary; int /*<<< orphan*/  max_dif_sgl_segments; int /*<<< orphan*/  max_hw_queues; int /*<<< orphan*/  targetport_delete; int /*<<< orphan*/  fcp_req_release; int /*<<< orphan*/  fcp_abort; int /*<<< orphan*/  fcp_op; int /*<<< orphan*/  xmt_ls_rsp; } ;
struct nvmet_fc_port_info {int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct nvmet_fc_tgtport*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nvmet_fc_tgtport* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nvmet_fc_alloc_ls_iodlist (struct nvmet_fc_tgtport*) ; 
 int /*<<< orphan*/  nvmet_fc_portentry_rebind_tgt (struct nvmet_fc_tgtport*) ; 
 int /*<<< orphan*/  nvmet_fc_target_list ; 
 int /*<<< orphan*/  nvmet_fc_tgtlock ; 
 int /*<<< orphan*/  nvmet_fc_tgtport_cnt ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
nvmet_fc_register_targetport(struct nvmet_fc_port_info *pinfo,
			struct nvmet_fc_target_template *template,
			struct device *dev,
			struct nvmet_fc_target_port **portptr)
{
	struct nvmet_fc_tgtport *newrec;
	unsigned long flags;
	int ret, idx;

	if (!template->xmt_ls_rsp || !template->fcp_op ||
	    !template->fcp_abort ||
	    !template->fcp_req_release || !template->targetport_delete ||
	    !template->max_hw_queues || !template->max_sgl_segments ||
	    !template->max_dif_sgl_segments || !template->dma_boundary) {
		ret = -EINVAL;
		goto out_regtgt_failed;
	}

	newrec = kzalloc((sizeof(*newrec) + template->target_priv_sz),
			 GFP_KERNEL);
	if (!newrec) {
		ret = -ENOMEM;
		goto out_regtgt_failed;
	}

	idx = ida_simple_get(&nvmet_fc_tgtport_cnt, 0, 0, GFP_KERNEL);
	if (idx < 0) {
		ret = -ENOSPC;
		goto out_fail_kfree;
	}

	if (!get_device(dev) && dev) {
		ret = -ENODEV;
		goto out_ida_put;
	}

	newrec->fc_target_port.node_name = pinfo->node_name;
	newrec->fc_target_port.port_name = pinfo->port_name;
	newrec->fc_target_port.private = &newrec[1];
	newrec->fc_target_port.port_id = pinfo->port_id;
	newrec->fc_target_port.port_num = idx;
	INIT_LIST_HEAD(&newrec->tgt_list);
	newrec->dev = dev;
	newrec->ops = template;
	spin_lock_init(&newrec->lock);
	INIT_LIST_HEAD(&newrec->ls_list);
	INIT_LIST_HEAD(&newrec->ls_busylist);
	INIT_LIST_HEAD(&newrec->assoc_list);
	kref_init(&newrec->ref);
	ida_init(&newrec->assoc_cnt);
	newrec->max_sg_cnt = template->max_sgl_segments;

	ret = nvmet_fc_alloc_ls_iodlist(newrec);
	if (ret) {
		ret = -ENOMEM;
		goto out_free_newrec;
	}

	nvmet_fc_portentry_rebind_tgt(newrec);

	spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	list_add_tail(&newrec->tgt_list, &nvmet_fc_target_list);
	spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);

	*portptr = &newrec->fc_target_port;
	return 0;

out_free_newrec:
	put_device(dev);
out_ida_put:
	ida_simple_remove(&nvmet_fc_tgtport_cnt, idx);
out_fail_kfree:
	kfree(newrec);
out_regtgt_failed:
	*portptr = NULL;
	return ret;
}
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
struct nvme_fc_remote_port {int port_num; int /*<<< orphan*/  port_state; int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_role; struct nvme_fc_rport* private; int /*<<< orphan*/ * localport; } ;
struct nvme_fc_rport {struct nvme_fc_remote_port remoteport; int /*<<< orphan*/  endp_list; struct nvme_fc_lport* lport; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  act_ctrl_cnt; int /*<<< orphan*/  ref; int /*<<< orphan*/  disc_list; int /*<<< orphan*/  ls_req_list; int /*<<< orphan*/  ctrl_list; } ;
struct nvme_fc_port_info {int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_role; } ;
struct nvme_fc_lport {int /*<<< orphan*/  endp_list; int /*<<< orphan*/  dev; int /*<<< orphan*/  localport; int /*<<< orphan*/  endp_cnt; TYPE_1__* ops; } ;
struct nvme_fc_local_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ remote_priv_sz; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  FC_OBJSTATE_ONLINE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct nvme_fc_rport*) ; 
 int PTR_ERR (struct nvme_fc_rport*) ; 
 int /*<<< orphan*/  __nvme_fc_set_dev_loss_tmo (struct nvme_fc_rport*,struct nvme_fc_port_info*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_fc_rport*) ; 
 struct nvme_fc_rport* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nvme_fc_lport* localport_to_lport (struct nvme_fc_local_port*) ; 
 struct nvme_fc_rport* nvme_fc_attach_to_suspended_rport (struct nvme_fc_lport*,struct nvme_fc_port_info*) ; 
 int /*<<< orphan*/  nvme_fc_lock ; 
 int /*<<< orphan*/  nvme_fc_lport_get (struct nvme_fc_lport*) ; 
 int /*<<< orphan*/  nvme_fc_lport_put (struct nvme_fc_lport*) ; 
 int /*<<< orphan*/  nvme_fc_signal_discovery_scan (struct nvme_fc_lport*,struct nvme_fc_rport*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
nvme_fc_register_remoteport(struct nvme_fc_local_port *localport,
				struct nvme_fc_port_info *pinfo,
				struct nvme_fc_remote_port **portptr)
{
	struct nvme_fc_lport *lport = localport_to_lport(localport);
	struct nvme_fc_rport *newrec;
	unsigned long flags;
	int ret, idx;

	if (!nvme_fc_lport_get(lport)) {
		ret = -ESHUTDOWN;
		goto out_reghost_failed;
	}

	/*
	 * look to see if there is already a remoteport that is waiting
	 * for a reconnect (within dev_loss_tmo) with the same WWN's.
	 * If so, transition to it and reconnect.
	 */
	newrec = nvme_fc_attach_to_suspended_rport(lport, pinfo);

	/* found an rport, but something about its state is bad */
	if (IS_ERR(newrec)) {
		ret = PTR_ERR(newrec);
		goto out_lport_put;

	/* found existing rport, which was resumed */
	} else if (newrec) {
		nvme_fc_lport_put(lport);
		__nvme_fc_set_dev_loss_tmo(newrec, pinfo);
		nvme_fc_signal_discovery_scan(lport, newrec);
		*portptr = &newrec->remoteport;
		return 0;
	}

	/* nothing found - allocate a new remoteport struct */

	newrec = kmalloc((sizeof(*newrec) + lport->ops->remote_priv_sz),
			 GFP_KERNEL);
	if (!newrec) {
		ret = -ENOMEM;
		goto out_lport_put;
	}

	idx = ida_simple_get(&lport->endp_cnt, 0, 0, GFP_KERNEL);
	if (idx < 0) {
		ret = -ENOSPC;
		goto out_kfree_rport;
	}

	INIT_LIST_HEAD(&newrec->endp_list);
	INIT_LIST_HEAD(&newrec->ctrl_list);
	INIT_LIST_HEAD(&newrec->ls_req_list);
	INIT_LIST_HEAD(&newrec->disc_list);
	kref_init(&newrec->ref);
	atomic_set(&newrec->act_ctrl_cnt, 0);
	spin_lock_init(&newrec->lock);
	newrec->remoteport.localport = &lport->localport;
	newrec->dev = lport->dev;
	newrec->lport = lport;
	newrec->remoteport.private = &newrec[1];
	newrec->remoteport.port_role = pinfo->port_role;
	newrec->remoteport.node_name = pinfo->node_name;
	newrec->remoteport.port_name = pinfo->port_name;
	newrec->remoteport.port_id = pinfo->port_id;
	newrec->remoteport.port_state = FC_OBJSTATE_ONLINE;
	newrec->remoteport.port_num = idx;
	__nvme_fc_set_dev_loss_tmo(newrec, pinfo);

	spin_lock_irqsave(&nvme_fc_lock, flags);
	list_add_tail(&newrec->endp_list, &lport->endp_list);
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	nvme_fc_signal_discovery_scan(lport, newrec);

	*portptr = &newrec->remoteport;
	return 0;

out_kfree_rport:
	kfree(newrec);
out_lport_put:
	nvme_fc_lport_put(lport);
out_reghost_failed:
	*portptr = NULL;
	return ret;
}
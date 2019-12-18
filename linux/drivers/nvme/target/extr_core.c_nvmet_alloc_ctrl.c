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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct nvmet_subsys {scalar_t__ type; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrls; scalar_t__ max_qid; } ;
struct nvmet_sq {int dummy; } ;
struct nvmet_req {int /*<<< orphan*/  ops; int /*<<< orphan*/  port; TYPE_2__* cqe; } ;
struct nvmet_ctrl {int cntlid; struct nvmet_ctrl* changed_ns_list; struct nvmet_ctrl* cqs; struct nvmet_ctrl* sqs; int /*<<< orphan*/  subsys_entry; int /*<<< orphan*/  error_lock; scalar_t__ err_counter; int /*<<< orphan*/  kato; struct nvmet_subsys* subsys; int /*<<< orphan*/  ops; int /*<<< orphan*/  aen_enabled; int /*<<< orphan*/  ref; int /*<<< orphan*/  hostnqn; int /*<<< orphan*/  subsysnqn; int /*<<< orphan*/  fatal_err_work; int /*<<< orphan*/  p2p_ns_map; int /*<<< orphan*/  async_events; int /*<<< orphan*/  async_event_work; int /*<<< orphan*/  port; int /*<<< orphan*/  lock; } ;
struct nvmet_cq {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {void* u32; } ;
struct TYPE_4__ {TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* IPO_IATTR_CONNECT_DATA (char const*) ; 
 int /*<<< orphan*/  NVMET_AEN_CFG_OPTIONAL ; 
 int /*<<< orphan*/  NVMET_DISC_KATO_MS ; 
 int /*<<< orphan*/  NVME_CNTLID_MAX ; 
 int /*<<< orphan*/  NVME_CNTLID_MIN ; 
 int /*<<< orphan*/  NVME_MAX_CHANGED_NAMESPACES ; 
 scalar_t__ NVME_NQN_DISC ; 
 int NVME_SC_CONNECT_CTRL_BUSY ; 
 int NVME_SC_CONNECT_INVALID_HOST ; 
 int NVME_SC_CONNECT_INVALID_PARAM ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INTERNAL ; 
 int /*<<< orphan*/  NVMF_NQN_SIZE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cntlid_ida ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvmet_ctrl*) ; 
 struct nvmet_ctrl* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nvmet_ctrl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_async_event_work ; 
 int /*<<< orphan*/  nvmet_config_sem ; 
 int /*<<< orphan*/  nvmet_fatal_error_handler ; 
 struct nvmet_subsys* nvmet_find_get_subsys (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nvmet_host_allowed (struct nvmet_subsys*,char const*) ; 
 int /*<<< orphan*/  nvmet_init_cap (struct nvmet_ctrl*) ; 
 int /*<<< orphan*/  nvmet_setup_p2p_ns_map (struct nvmet_ctrl*,struct nvmet_req*) ; 
 int /*<<< orphan*/  nvmet_start_keep_alive_timer (struct nvmet_ctrl*) ; 
 int /*<<< orphan*/  nvmet_subsys_put (struct nvmet_subsys*) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,char const*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

u16 nvmet_alloc_ctrl(const char *subsysnqn, const char *hostnqn,
		struct nvmet_req *req, u32 kato, struct nvmet_ctrl **ctrlp)
{
	struct nvmet_subsys *subsys;
	struct nvmet_ctrl *ctrl;
	int ret;
	u16 status;

	status = NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
	subsys = nvmet_find_get_subsys(req->port, subsysnqn);
	if (!subsys) {
		pr_warn("connect request for invalid subsystem %s!\n",
			subsysnqn);
		req->cqe->result.u32 = IPO_IATTR_CONNECT_DATA(subsysnqn);
		goto out;
	}

	status = NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
	down_read(&nvmet_config_sem);
	if (!nvmet_host_allowed(subsys, hostnqn)) {
		pr_info("connect by host %s for subsystem %s not allowed\n",
			hostnqn, subsysnqn);
		req->cqe->result.u32 = IPO_IATTR_CONNECT_DATA(hostnqn);
		up_read(&nvmet_config_sem);
		status = NVME_SC_CONNECT_INVALID_HOST | NVME_SC_DNR;
		goto out_put_subsystem;
	}
	up_read(&nvmet_config_sem);

	status = NVME_SC_INTERNAL;
	ctrl = kzalloc(sizeof(*ctrl), GFP_KERNEL);
	if (!ctrl)
		goto out_put_subsystem;
	mutex_init(&ctrl->lock);

	nvmet_init_cap(ctrl);

	ctrl->port = req->port;

	INIT_WORK(&ctrl->async_event_work, nvmet_async_event_work);
	INIT_LIST_HEAD(&ctrl->async_events);
	INIT_RADIX_TREE(&ctrl->p2p_ns_map, GFP_KERNEL);
	INIT_WORK(&ctrl->fatal_err_work, nvmet_fatal_error_handler);

	memcpy(ctrl->subsysnqn, subsysnqn, NVMF_NQN_SIZE);
	memcpy(ctrl->hostnqn, hostnqn, NVMF_NQN_SIZE);

	kref_init(&ctrl->ref);
	ctrl->subsys = subsys;
	WRITE_ONCE(ctrl->aen_enabled, NVMET_AEN_CFG_OPTIONAL);

	ctrl->changed_ns_list = kmalloc_array(NVME_MAX_CHANGED_NAMESPACES,
			sizeof(__le32), GFP_KERNEL);
	if (!ctrl->changed_ns_list)
		goto out_free_ctrl;

	ctrl->cqs = kcalloc(subsys->max_qid + 1,
			sizeof(struct nvmet_cq *),
			GFP_KERNEL);
	if (!ctrl->cqs)
		goto out_free_changed_ns_list;

	ctrl->sqs = kcalloc(subsys->max_qid + 1,
			sizeof(struct nvmet_sq *),
			GFP_KERNEL);
	if (!ctrl->sqs)
		goto out_free_cqs;

	ret = ida_simple_get(&cntlid_ida,
			     NVME_CNTLID_MIN, NVME_CNTLID_MAX,
			     GFP_KERNEL);
	if (ret < 0) {
		status = NVME_SC_CONNECT_CTRL_BUSY | NVME_SC_DNR;
		goto out_free_sqs;
	}
	ctrl->cntlid = ret;

	ctrl->ops = req->ops;

	/*
	 * Discovery controllers may use some arbitrary high value
	 * in order to cleanup stale discovery sessions
	 */
	if ((ctrl->subsys->type == NVME_NQN_DISC) && !kato)
		kato = NVMET_DISC_KATO_MS;

	/* keep-alive timeout in seconds */
	ctrl->kato = DIV_ROUND_UP(kato, 1000);

	ctrl->err_counter = 0;
	spin_lock_init(&ctrl->error_lock);

	nvmet_start_keep_alive_timer(ctrl);

	mutex_lock(&subsys->lock);
	list_add_tail(&ctrl->subsys_entry, &subsys->ctrls);
	nvmet_setup_p2p_ns_map(ctrl, req);
	mutex_unlock(&subsys->lock);

	*ctrlp = ctrl;
	return 0;

out_free_sqs:
	kfree(ctrl->sqs);
out_free_cqs:
	kfree(ctrl->cqs);
out_free_changed_ns_list:
	kfree(ctrl->changed_ns_list);
out_free_ctrl:
	kfree(ctrl);
out_put_subsystem:
	nvmet_subsys_put(subsys);
out:
	return status;
}
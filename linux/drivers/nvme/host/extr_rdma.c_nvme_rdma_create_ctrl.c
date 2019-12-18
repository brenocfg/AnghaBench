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
struct nvmf_ctrl_options {int mask; int /*<<< orphan*/  subsysnqn; int /*<<< orphan*/  kato; scalar_t__ queue_size; scalar_t__ nr_poll_queues; scalar_t__ nr_write_queues; scalar_t__ nr_io_queues; int /*<<< orphan*/  duplicate_connect; int /*<<< orphan*/  host_traddr; int /*<<< orphan*/ * trsvcid; int /*<<< orphan*/  traddr; } ;
struct nvme_ctrl {struct nvmf_ctrl_options* opts; int /*<<< orphan*/  device; scalar_t__ queue_count; int /*<<< orphan*/  kato; scalar_t__ sqsize; int /*<<< orphan*/  reset_work; } ;
struct nvme_rdma_ctrl {struct nvme_rdma_ctrl* queues; struct nvme_ctrl ctrl; int /*<<< orphan*/  list; int /*<<< orphan*/  addr; int /*<<< orphan*/  err_work; int /*<<< orphan*/  reconnect_work; int /*<<< orphan*/  src_addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EALREADY ; 
 int EIO ; 
 int ENOMEM ; 
 struct nvme_ctrl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVME_CTRL_CONNECTING ; 
 int /*<<< orphan*/  NVME_RDMA_IP_PORT ; 
 int NVMF_OPT_HOST_TRADDR ; 
 int NVMF_OPT_TRSVCID ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __stringify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int inet_pton_with_scope (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 struct nvme_rdma_ctrl* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_rdma_ctrl*) ; 
 int /*<<< orphan*/ * kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nvme_rdma_ctrl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvme_change_ctrl_state (struct nvme_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_get_ctrl (struct nvme_ctrl*) ; 
 int nvme_init_ctrl (struct nvme_ctrl*,struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_put_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_rdma_ctrl_list ; 
 int /*<<< orphan*/  nvme_rdma_ctrl_mutex ; 
 int /*<<< orphan*/  nvme_rdma_ctrl_ops ; 
 int /*<<< orphan*/  nvme_rdma_error_recovery_work ; 
 scalar_t__ nvme_rdma_existing_controller (struct nvmf_ctrl_options*) ; 
 int /*<<< orphan*/  nvme_rdma_reconnect_ctrl_work ; 
 int /*<<< orphan*/  nvme_rdma_reset_ctrl_work ; 
 int nvme_rdma_setup_ctrl (struct nvme_rdma_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_uninit_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static struct nvme_ctrl *nvme_rdma_create_ctrl(struct device *dev,
		struct nvmf_ctrl_options *opts)
{
	struct nvme_rdma_ctrl *ctrl;
	int ret;
	bool changed;

	ctrl = kzalloc(sizeof(*ctrl), GFP_KERNEL);
	if (!ctrl)
		return ERR_PTR(-ENOMEM);
	ctrl->ctrl.opts = opts;
	INIT_LIST_HEAD(&ctrl->list);

	if (!(opts->mask & NVMF_OPT_TRSVCID)) {
		opts->trsvcid =
			kstrdup(__stringify(NVME_RDMA_IP_PORT), GFP_KERNEL);
		if (!opts->trsvcid) {
			ret = -ENOMEM;
			goto out_free_ctrl;
		}
		opts->mask |= NVMF_OPT_TRSVCID;
	}

	ret = inet_pton_with_scope(&init_net, AF_UNSPEC,
			opts->traddr, opts->trsvcid, &ctrl->addr);
	if (ret) {
		pr_err("malformed address passed: %s:%s\n",
			opts->traddr, opts->trsvcid);
		goto out_free_ctrl;
	}

	if (opts->mask & NVMF_OPT_HOST_TRADDR) {
		ret = inet_pton_with_scope(&init_net, AF_UNSPEC,
			opts->host_traddr, NULL, &ctrl->src_addr);
		if (ret) {
			pr_err("malformed src address passed: %s\n",
			       opts->host_traddr);
			goto out_free_ctrl;
		}
	}

	if (!opts->duplicate_connect && nvme_rdma_existing_controller(opts)) {
		ret = -EALREADY;
		goto out_free_ctrl;
	}

	INIT_DELAYED_WORK(&ctrl->reconnect_work,
			nvme_rdma_reconnect_ctrl_work);
	INIT_WORK(&ctrl->err_work, nvme_rdma_error_recovery_work);
	INIT_WORK(&ctrl->ctrl.reset_work, nvme_rdma_reset_ctrl_work);

	ctrl->ctrl.queue_count = opts->nr_io_queues + opts->nr_write_queues +
				opts->nr_poll_queues + 1;
	ctrl->ctrl.sqsize = opts->queue_size - 1;
	ctrl->ctrl.kato = opts->kato;

	ret = -ENOMEM;
	ctrl->queues = kcalloc(ctrl->ctrl.queue_count, sizeof(*ctrl->queues),
				GFP_KERNEL);
	if (!ctrl->queues)
		goto out_free_ctrl;

	ret = nvme_init_ctrl(&ctrl->ctrl, dev, &nvme_rdma_ctrl_ops,
				0 /* no quirks, we're perfect! */);
	if (ret)
		goto out_kfree_queues;

	changed = nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING);
	WARN_ON_ONCE(!changed);

	ret = nvme_rdma_setup_ctrl(ctrl, true);
	if (ret)
		goto out_uninit_ctrl;

	dev_info(ctrl->ctrl.device, "new ctrl: NQN \"%s\", addr %pISpcs\n",
		ctrl->ctrl.opts->subsysnqn, &ctrl->addr);

	nvme_get_ctrl(&ctrl->ctrl);

	mutex_lock(&nvme_rdma_ctrl_mutex);
	list_add_tail(&ctrl->list, &nvme_rdma_ctrl_list);
	mutex_unlock(&nvme_rdma_ctrl_mutex);

	return &ctrl->ctrl;

out_uninit_ctrl:
	nvme_uninit_ctrl(&ctrl->ctrl);
	nvme_put_ctrl(&ctrl->ctrl);
	if (ret > 0)
		ret = -EIO;
	return ERR_PTR(ret);
out_kfree_queues:
	kfree(ctrl->queues);
out_free_ctrl:
	kfree(ctrl);
	return ERR_PTR(ret);
}
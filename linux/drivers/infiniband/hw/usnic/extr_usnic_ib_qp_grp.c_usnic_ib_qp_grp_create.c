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
struct usnic_vnic_res_spec {int dummy; } ;
struct usnic_transport_spec {int trans_type; } ;
struct usnic_ib_vf {int /*<<< orphan*/  vnic; int /*<<< orphan*/  lock; } ;
struct usnic_ib_qp_grp_flow {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  qp_num; } ;
struct usnic_ib_qp_grp {struct usnic_ib_qp_grp_flow* res_chunk_list; int /*<<< orphan*/  grp_id; TYPE_1__ ibqp; int /*<<< orphan*/  owner_pid; int /*<<< orphan*/  state; struct usnic_fwd_dev* ufdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  flows_lst; } ;
struct usnic_ib_pd {int dummy; } ;
struct usnic_fwd_dev {int dummy; } ;
typedef  enum usnic_transport_type { ____Placeholder_usnic_transport_type } usnic_transport_type ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 struct usnic_ib_qp_grp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IB_QPS_RESET ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR_OR_NULL (struct usnic_ib_qp_grp_flow*) ; 
 int PTR_ERR (struct usnic_ib_qp_grp_flow*) ; 
 struct usnic_ib_qp_grp_flow* alloc_res_chunk_list (int /*<<< orphan*/ ,struct usnic_vnic_res_spec*,struct usnic_ib_qp_grp*) ; 
 struct usnic_ib_qp_grp_flow* create_and_add_flow (struct usnic_ib_qp_grp*,struct usnic_transport_spec*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  free_qp_grp_res (struct usnic_ib_qp_grp_flow*) ; 
 int /*<<< orphan*/  kfree (struct usnic_ib_qp_grp*) ; 
 struct usnic_ib_qp_grp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_spec (struct usnic_vnic_res_spec*) ; 
 int /*<<< orphan*/ * min_transport_spec ; 
 int qp_grp_and_vf_bind (struct usnic_ib_vf*,struct usnic_ib_pd*,struct usnic_ib_qp_grp*) ; 
 int /*<<< orphan*/  qp_grp_and_vf_unbind (struct usnic_ib_qp_grp*) ; 
 int qp_grp_id_from_flow (struct usnic_ib_qp_grp_flow*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_and_remove_flow (struct usnic_ib_qp_grp_flow*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_err (char*,int) ; 
 int /*<<< orphan*/  usnic_ib_sysfs_qpn_add (struct usnic_ib_qp_grp*) ; 
 int usnic_vnic_res_spec_satisfied (int /*<<< orphan*/ *,struct usnic_vnic_res_spec*) ; 

struct usnic_ib_qp_grp *
usnic_ib_qp_grp_create(struct usnic_fwd_dev *ufdev, struct usnic_ib_vf *vf,
			struct usnic_ib_pd *pd,
			struct usnic_vnic_res_spec *res_spec,
			struct usnic_transport_spec *transport_spec)
{
	struct usnic_ib_qp_grp *qp_grp;
	int err;
	enum usnic_transport_type transport = transport_spec->trans_type;
	struct usnic_ib_qp_grp_flow *qp_flow;

	lockdep_assert_held(&vf->lock);

	err = usnic_vnic_res_spec_satisfied(&min_transport_spec[transport],
						res_spec);
	if (err) {
		usnic_err("Spec does not meet minimum req for transport %d\n",
				transport);
		log_spec(res_spec);
		return ERR_PTR(err);
	}

	qp_grp = kzalloc(sizeof(*qp_grp), GFP_ATOMIC);
	if (!qp_grp)
		return NULL;

	qp_grp->res_chunk_list = alloc_res_chunk_list(vf->vnic, res_spec,
							qp_grp);
	if (IS_ERR_OR_NULL(qp_grp->res_chunk_list)) {
		err = qp_grp->res_chunk_list ?
				PTR_ERR(qp_grp->res_chunk_list) : -ENOMEM;
		goto out_free_qp_grp;
	}

	err = qp_grp_and_vf_bind(vf, pd, qp_grp);
	if (err)
		goto out_free_res;

	INIT_LIST_HEAD(&qp_grp->flows_lst);
	spin_lock_init(&qp_grp->lock);
	qp_grp->ufdev = ufdev;
	qp_grp->state = IB_QPS_RESET;
	qp_grp->owner_pid = current->pid;

	qp_flow = create_and_add_flow(qp_grp, transport_spec);
	if (IS_ERR_OR_NULL(qp_flow)) {
		usnic_err("Unable to create and add flow with err %ld\n",
				PTR_ERR(qp_flow));
		err = qp_flow ? PTR_ERR(qp_flow) : -EFAULT;
		goto out_qp_grp_vf_unbind;
	}

	err = qp_grp_id_from_flow(qp_flow, &qp_grp->grp_id);
	if (err)
		goto out_release_flow;
	qp_grp->ibqp.qp_num = qp_grp->grp_id;

	usnic_ib_sysfs_qpn_add(qp_grp);

	return qp_grp;

out_release_flow:
	release_and_remove_flow(qp_flow);
out_qp_grp_vf_unbind:
	qp_grp_and_vf_unbind(qp_grp);
out_free_res:
	free_qp_grp_res(qp_grp->res_chunk_list);
out_free_qp_grp:
	kfree(qp_grp);

	return ERR_PTR(err);
}
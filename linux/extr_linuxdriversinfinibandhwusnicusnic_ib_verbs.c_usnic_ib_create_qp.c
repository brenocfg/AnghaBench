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
struct usnic_transport_spec {size_t trans_type; } ;
struct usnic_ib_ucontext {int /*<<< orphan*/  qp_grp_list; } ;
struct ib_qp {int dummy; } ;
struct usnic_ib_qp_grp {struct ib_qp ibqp; int /*<<< orphan*/  vf; int /*<<< orphan*/  link; struct usnic_ib_ucontext* ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct usnic_ib_dev {int /*<<< orphan*/  usdev_lock; TYPE_2__ ib_dev; } ;
struct usnic_ib_create_qp_cmd {struct usnic_transport_spec spec; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_init_attr {scalar_t__ send_cq; scalar_t__ recv_cq; int /*<<< orphan*/  qp_type; scalar_t__ create_flags; } ;
struct ib_pd {int /*<<< orphan*/  device; TYPE_1__* uobject; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_qp* ERR_PTR (int) ; 
 int /*<<< orphan*/  IB_QPT_UD ; 
 scalar_t__ IS_ERR_OR_NULL (struct usnic_ib_qp_grp*) ; 
 int PTR_ERR (struct usnic_ib_qp_grp*) ; 
 int /*<<< orphan*/  USNIC_VNIC_RES_TYPE_CQ ; 
 int create_qp_validate_user_data (struct usnic_ib_create_qp_cmd) ; 
 struct usnic_ib_qp_grp* find_free_vf_and_create_qp_grp (struct usnic_ib_dev*,int /*<<< orphan*/ ,struct usnic_transport_spec*,struct usnic_vnic_res_spec*) ; 
 int ib_copy_from_udata (struct usnic_ib_create_qp_cmd*,struct ib_udata*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usnic_vnic_res_spec* min_transport_spec ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qp_grp_destroy (struct usnic_ib_qp_grp*) ; 
 int /*<<< orphan*/  to_upd (struct ib_pd*) ; 
 struct usnic_ib_dev* to_usdev (int /*<<< orphan*/ ) ; 
 struct usnic_ib_ucontext* to_uucontext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ,...) ; 
 int usnic_ib_fill_create_qp_resp (struct usnic_ib_qp_grp*,struct ib_udata*) ; 
 int /*<<< orphan*/  usnic_ib_log_vf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_vnic_res_spec_update (struct usnic_vnic_res_spec*,int /*<<< orphan*/ ,int) ; 

struct ib_qp *usnic_ib_create_qp(struct ib_pd *pd,
					struct ib_qp_init_attr *init_attr,
					struct ib_udata *udata)
{
	int err;
	struct usnic_ib_dev *us_ibdev;
	struct usnic_ib_qp_grp *qp_grp;
	struct usnic_ib_ucontext *ucontext;
	int cq_cnt;
	struct usnic_vnic_res_spec res_spec;
	struct usnic_ib_create_qp_cmd cmd;
	struct usnic_transport_spec trans_spec;

	usnic_dbg("\n");

	ucontext = to_uucontext(pd->uobject->context);
	us_ibdev = to_usdev(pd->device);

	if (init_attr->create_flags)
		return ERR_PTR(-EINVAL);

	err = ib_copy_from_udata(&cmd, udata, sizeof(cmd));
	if (err) {
		usnic_err("%s: cannot copy udata for create_qp\n",
				us_ibdev->ib_dev.name);
		return ERR_PTR(-EINVAL);
	}

	err = create_qp_validate_user_data(cmd);
	if (err) {
		usnic_err("%s: Failed to validate user data\n",
				us_ibdev->ib_dev.name);
		return ERR_PTR(-EINVAL);
	}

	if (init_attr->qp_type != IB_QPT_UD) {
		usnic_err("%s asked to make a non-UD QP: %d\n",
				us_ibdev->ib_dev.name, init_attr->qp_type);
		return ERR_PTR(-EINVAL);
	}

	trans_spec = cmd.spec;
	mutex_lock(&us_ibdev->usdev_lock);
	cq_cnt = (init_attr->send_cq == init_attr->recv_cq) ? 1 : 2;
	res_spec = min_transport_spec[trans_spec.trans_type];
	usnic_vnic_res_spec_update(&res_spec, USNIC_VNIC_RES_TYPE_CQ, cq_cnt);
	qp_grp = find_free_vf_and_create_qp_grp(us_ibdev, to_upd(pd),
						&trans_spec,
						&res_spec);
	if (IS_ERR_OR_NULL(qp_grp)) {
		err = qp_grp ? PTR_ERR(qp_grp) : -ENOMEM;
		goto out_release_mutex;
	}

	err = usnic_ib_fill_create_qp_resp(qp_grp, udata);
	if (err) {
		err = -EBUSY;
		goto out_release_qp_grp;
	}

	qp_grp->ctx = ucontext;
	list_add_tail(&qp_grp->link, &ucontext->qp_grp_list);
	usnic_ib_log_vf(qp_grp->vf);
	mutex_unlock(&us_ibdev->usdev_lock);
	return &qp_grp->ibqp;

out_release_qp_grp:
	qp_grp_destroy(qp_grp);
out_release_mutex:
	mutex_unlock(&us_ibdev->usdev_lock);
	return ERR_PTR(err);
}
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
struct ib_recv_wr {struct ib_recv_wr* next; int /*<<< orphan*/  num_sge; int /*<<< orphan*/  sg_list; int /*<<< orphan*/  wr_id; } ;
struct ib_qp {int dummy; } ;
struct i40iw_sge {int dummy; } ;
struct TYPE_4__ {int (* iw_post_receive ) (struct i40iw_qp_uk*,struct i40iw_post_rq_info*) ;} ;
struct i40iw_qp_uk {TYPE_2__ ops; } ;
struct TYPE_3__ {struct i40iw_qp_uk qp_uk; } ;
struct i40iw_qp {int /*<<< orphan*/  lock; scalar_t__ flush_issued; TYPE_1__ sc_qp; } ;
struct i40iw_post_rq_info {struct i40iw_sge* sg_list; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  num_sges; } ;
typedef  int /*<<< orphan*/  post_recv ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int I40IW_ERR_QP_TOOMANY_WRS_POSTED ; 
 int I40IW_MAX_WQ_FRAGMENT_COUNT ; 
 int /*<<< orphan*/  i40iw_copy_sg_list (struct i40iw_sge*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,int) ; 
 int /*<<< orphan*/  memset (struct i40iw_post_rq_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct i40iw_qp_uk*,struct i40iw_post_rq_info*) ; 

__attribute__((used)) static int i40iw_post_recv(struct ib_qp *ibqp, const struct ib_recv_wr *ib_wr,
			   const struct ib_recv_wr **bad_wr)
{
	struct i40iw_qp *iwqp;
	struct i40iw_qp_uk *ukqp;
	struct i40iw_post_rq_info post_recv;
	struct i40iw_sge sg_list[I40IW_MAX_WQ_FRAGMENT_COUNT];
	enum i40iw_status_code ret = 0;
	unsigned long flags;
	int err = 0;

	iwqp = (struct i40iw_qp *)ibqp;
	ukqp = &iwqp->sc_qp.qp_uk;

	memset(&post_recv, 0, sizeof(post_recv));
	spin_lock_irqsave(&iwqp->lock, flags);

	if (iwqp->flush_issued) {
		err = -EINVAL;
		goto out;
	}

	while (ib_wr) {
		post_recv.num_sges = ib_wr->num_sge;
		post_recv.wr_id = ib_wr->wr_id;
		i40iw_copy_sg_list(sg_list, ib_wr->sg_list, ib_wr->num_sge);
		post_recv.sg_list = sg_list;
		ret = ukqp->ops.iw_post_receive(ukqp, &post_recv);
		if (ret) {
			i40iw_pr_err(" post_recv err %d\n", ret);
			if (ret == I40IW_ERR_QP_TOOMANY_WRS_POSTED)
				err = -ENOMEM;
			else
				err = -EINVAL;
			*bad_wr = ib_wr;
			goto out;
		}
		ib_wr = ib_wr->next;
	}
 out:
	spin_unlock_irqrestore(&iwqp->lock, flags);
	return err;
}
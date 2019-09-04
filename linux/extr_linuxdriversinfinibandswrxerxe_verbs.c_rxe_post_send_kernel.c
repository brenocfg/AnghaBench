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
struct TYPE_6__ {int /*<<< orphan*/  task; } ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  task; } ;
struct rxe_qp {TYPE_3__ comp; TYPE_2__ req; } ;
struct ib_send_wr {int send_flags; int num_sge; struct ib_send_wr* next; TYPE_1__* sg_list; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {scalar_t__ length; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_SEND_INLINE ; 
 scalar_t__ QP_STATE_ERROR ; 
 unsigned int WR_INLINE_MASK ; 
 int post_one_send (struct rxe_qp*,struct ib_send_wr const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 
 unsigned int wr_opcode_mask (int /*<<< orphan*/ ,struct rxe_qp*) ; 

__attribute__((used)) static int rxe_post_send_kernel(struct rxe_qp *qp, const struct ib_send_wr *wr,
				const struct ib_send_wr **bad_wr)
{
	int err = 0;
	unsigned int mask;
	unsigned int length = 0;
	int i;

	while (wr) {
		mask = wr_opcode_mask(wr->opcode, qp);
		if (unlikely(!mask)) {
			err = -EINVAL;
			*bad_wr = wr;
			break;
		}

		if (unlikely((wr->send_flags & IB_SEND_INLINE) &&
			     !(mask & WR_INLINE_MASK))) {
			err = -EINVAL;
			*bad_wr = wr;
			break;
		}

		length = 0;
		for (i = 0; i < wr->num_sge; i++)
			length += wr->sg_list[i].length;

		err = post_one_send(qp, wr, mask, length);

		if (err) {
			*bad_wr = wr;
			break;
		}
		wr = wr->next;
	}

	rxe_run_task(&qp->req.task, 1);
	if (unlikely(qp->req.state == QP_STATE_ERROR))
		rxe_run_task(&qp->comp.task, 1);

	return err;
}
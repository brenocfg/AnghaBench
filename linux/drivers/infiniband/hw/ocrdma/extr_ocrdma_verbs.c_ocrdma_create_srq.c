#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int max_cnt; } ;
struct ocrdma_srq {int bit_fields_len; int /*<<< orphan*/  idx_bit_fields; int /*<<< orphan*/  rqe_wr_id_tbl; TYPE_3__ rq; scalar_t__ db; struct ocrdma_pd* pd; int /*<<< orphan*/  q_lock; } ;
struct ocrdma_pd {int id; } ;
struct TYPE_6__ {int db_page_size; scalar_t__ db; } ;
struct TYPE_5__ {scalar_t__ max_recv_sge; scalar_t__ max_rqe; } ;
struct ocrdma_dev {TYPE_2__ nic_info; TYPE_1__ attr; } ;
struct ib_udata {int dummy; } ;
struct TYPE_8__ {scalar_t__ max_sge; scalar_t__ max_wr; scalar_t__ srq_limit; } ;
struct ib_srq_init_attr {TYPE_4__ attr; } ;
struct ib_srq {int /*<<< orphan*/  device; int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 struct ocrdma_pd* get_ocrdma_pd (int /*<<< orphan*/ ) ; 
 struct ocrdma_srq* get_ocrdma_srq (struct ib_srq*) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int ocrdma_copy_srq_uresp (struct ocrdma_dev*,struct ocrdma_srq*,struct ib_udata*) ; 
 int ocrdma_mbx_create_srq (struct ocrdma_dev*,struct ocrdma_srq*,struct ib_srq_init_attr*,struct ocrdma_pd*) ; 
 int /*<<< orphan*/  ocrdma_mbx_destroy_srq (struct ocrdma_dev*,struct ocrdma_srq*) ; 
 int ocrdma_mbx_modify_srq (struct ocrdma_srq*,TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ocrdma_create_srq(struct ib_srq *ibsrq, struct ib_srq_init_attr *init_attr,
		      struct ib_udata *udata)
{
	int status;
	struct ocrdma_pd *pd = get_ocrdma_pd(ibsrq->pd);
	struct ocrdma_dev *dev = get_ocrdma_dev(ibsrq->device);
	struct ocrdma_srq *srq = get_ocrdma_srq(ibsrq);

	if (init_attr->attr.max_sge > dev->attr.max_recv_sge)
		return -EINVAL;
	if (init_attr->attr.max_wr > dev->attr.max_rqe)
		return -EINVAL;

	spin_lock_init(&srq->q_lock);
	srq->pd = pd;
	srq->db = dev->nic_info.db + (pd->id * dev->nic_info.db_page_size);
	status = ocrdma_mbx_create_srq(dev, srq, init_attr, pd);
	if (status)
		return status;

	if (!udata) {
		srq->rqe_wr_id_tbl = kcalloc(srq->rq.max_cnt, sizeof(u64),
					     GFP_KERNEL);
		if (!srq->rqe_wr_id_tbl) {
			status = -ENOMEM;
			goto arm_err;
		}

		srq->bit_fields_len = (srq->rq.max_cnt / 32) +
		    (srq->rq.max_cnt % 32 ? 1 : 0);
		srq->idx_bit_fields =
		    kmalloc_array(srq->bit_fields_len, sizeof(u32),
				  GFP_KERNEL);
		if (!srq->idx_bit_fields) {
			status = -ENOMEM;
			goto arm_err;
		}
		memset(srq->idx_bit_fields, 0xff,
		       srq->bit_fields_len * sizeof(u32));
	}

	if (init_attr->attr.srq_limit) {
		status = ocrdma_mbx_modify_srq(srq, &init_attr->attr);
		if (status)
			goto arm_err;
	}

	if (udata) {
		status = ocrdma_copy_srq_uresp(dev, srq, udata);
		if (status)
			goto arm_err;
	}

	return 0;

arm_err:
	ocrdma_mbx_destroy_srq(dev, srq);
	kfree(srq->rqe_wr_id_tbl);
	kfree(srq->idx_bit_fields);
	return status;
}
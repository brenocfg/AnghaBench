#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ib_qp {int dummy; } ;
struct TYPE_9__ {void* in; } ;
struct mlx5_ib_qp {struct ib_qp ibqp; int /*<<< orphan*/  state; int /*<<< orphan*/  qp_sub_type; TYPE_2__ dct; } ;
struct mlx5_ib_create_qp {int /*<<< orphan*/  access_key; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  srq; } ;
struct ib_pd {TYPE_1__* uobject; } ;
struct TYPE_11__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_14__ {TYPE_4__ mcq; } ;
struct TYPE_13__ {int /*<<< orphan*/  pdn; } ;
struct TYPE_10__ {int /*<<< orphan*/  srqn; } ;
struct TYPE_12__ {TYPE_3__ msrq; } ;
struct TYPE_8__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_qp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_QPS_RESET ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_IB_DEFAULT_UIDX ; 
 int /*<<< orphan*/  MLX5_IB_QPT_DCT ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,struct ib_pd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 struct ib_pd* cqn ; 
 int /*<<< orphan*/  create_dct_in ; 
 int /*<<< orphan*/  dc_access_key ; 
 int /*<<< orphan*/  dct_context_entry ; 
 int get_qp_user_index (int /*<<< orphan*/ ,struct mlx5_ib_create_qp*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_qp*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_pd* srqn_xrqn ; 
 TYPE_7__* to_mcq (int /*<<< orphan*/ ) ; 
 TYPE_6__* to_mpd (struct ib_pd*) ; 
 TYPE_5__* to_msrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mucontext (int /*<<< orphan*/ ) ; 
 struct ib_pd* user_index ; 

__attribute__((used)) static struct ib_qp *mlx5_ib_create_dct(struct ib_pd *pd,
					struct ib_qp_init_attr *attr,
					struct mlx5_ib_create_qp *ucmd)
{
	struct mlx5_ib_qp *qp;
	int err = 0;
	u32 uidx = MLX5_IB_DEFAULT_UIDX;
	void *dctc;

	if (!attr->srq || !attr->recv_cq)
		return ERR_PTR(-EINVAL);

	err = get_qp_user_index(to_mucontext(pd->uobject->context),
				ucmd, sizeof(*ucmd), &uidx);
	if (err)
		return ERR_PTR(err);

	qp = kzalloc(sizeof(*qp), GFP_KERNEL);
	if (!qp)
		return ERR_PTR(-ENOMEM);

	qp->dct.in = kzalloc(MLX5_ST_SZ_BYTES(create_dct_in), GFP_KERNEL);
	if (!qp->dct.in) {
		err = -ENOMEM;
		goto err_free;
	}

	dctc = MLX5_ADDR_OF(create_dct_in, qp->dct.in, dct_context_entry);
	qp->qp_sub_type = MLX5_IB_QPT_DCT;
	MLX5_SET(dctc, dctc, pd, to_mpd(pd)->pdn);
	MLX5_SET(dctc, dctc, srqn_xrqn, to_msrq(attr->srq)->msrq.srqn);
	MLX5_SET(dctc, dctc, cqn, to_mcq(attr->recv_cq)->mcq.cqn);
	MLX5_SET64(dctc, dctc, dc_access_key, ucmd->access_key);
	MLX5_SET(dctc, dctc, user_index, uidx);

	qp->state = IB_QPS_RESET;

	return &qp->ibqp;
err_free:
	kfree(qp);
	return ERR_PTR(err);
}
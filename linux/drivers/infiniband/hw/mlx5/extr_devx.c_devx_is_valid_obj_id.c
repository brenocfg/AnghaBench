#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct uverbs_attr_bundle {int /*<<< orphan*/  driver_udata; } ;
struct TYPE_29__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_30__ {TYPE_6__ mqp; } ;
struct mlx5_ib_sq {int /*<<< orphan*/  tisn; TYPE_7__ base; } ;
struct TYPE_27__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_28__ {TYPE_4__ mqp; } ;
struct mlx5_ib_rq {int /*<<< orphan*/  tirn; TYPE_5__ base; } ;
struct mlx5_ib_raw_packet_qp {struct mlx5_ib_sq sq; struct mlx5_ib_rq rq; } ;
struct TYPE_18__ {int qp_type; int /*<<< orphan*/  qp_num; } ;
struct TYPE_31__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_32__ {TYPE_8__ mqp; } ;
struct TYPE_17__ {TYPE_9__ mdct; } ;
struct mlx5_ib_qp {int flags; TYPE_11__ ibqp; TYPE_10__ dct; struct mlx5_ib_raw_packet_qp raw_packet_qp; } ;
struct mlx5_ib_dev {TYPE_3__* mdev; } ;
struct TYPE_25__ {int /*<<< orphan*/  res; } ;
struct mlx5_core_srq {int /*<<< orphan*/  srqn; TYPE_2__ common; } ;
struct ib_uobject {scalar_t__ object; } ;
struct devx_obj {int /*<<< orphan*/  obj_id; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_26__ {int /*<<< orphan*/  issi; } ;
struct TYPE_24__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_23__ {TYPE_1__ mcq; } ;
struct TYPE_19__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_22__ {TYPE_12__ core_qp; } ;
struct TYPE_21__ {int /*<<< orphan*/  rqtn; } ;
struct TYPE_20__ {struct mlx5_core_srq msrq; } ;

/* Variables and functions */
 int IB_QPT_RAW_PACKET ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_CQ ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_DCT ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_QP ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_RMP ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_RQ ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_RQT ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_SQ ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_SRQ ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_TIR ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_TIS ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_XRC_SRQ ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_XRQ ; 
#define  MLX5_IB_OBJECT_DEVX_OBJ 135 
 int MLX5_IB_QPT_DCT ; 
 int MLX5_IB_QP_UNDERLAY ; 
#define  MLX5_RES_XRQ 134 
#define  MLX5_RES_XSRQ 133 
#define  UVERBS_OBJECT_CQ 132 
#define  UVERBS_OBJECT_QP 131 
#define  UVERBS_OBJECT_RWQ_IND_TBL 130 
#define  UVERBS_OBJECT_SRQ 129 
#define  UVERBS_OBJECT_WQ 128 
 int /*<<< orphan*/  devx_get_obj_id (void const*) ; 
 int /*<<< orphan*/  get_enc_obj_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* mlx5_udata_to_mdev (int /*<<< orphan*/ *) ; 
 TYPE_16__* to_mcq (scalar_t__) ; 
 struct mlx5_ib_qp* to_mqp (scalar_t__) ; 
 TYPE_15__* to_mrwq (scalar_t__) ; 
 TYPE_14__* to_mrwq_ind_table (scalar_t__) ; 
 TYPE_13__* to_msrq (scalar_t__) ; 
 int uobj_get_object_id (struct ib_uobject*) ; 

__attribute__((used)) static bool devx_is_valid_obj_id(struct uverbs_attr_bundle *attrs,
				 struct ib_uobject *uobj, const void *in)
{
	struct mlx5_ib_dev *dev = mlx5_udata_to_mdev(&attrs->driver_udata);
	u64 obj_id = devx_get_obj_id(in);

	if (!obj_id)
		return false;

	switch (uobj_get_object_id(uobj)) {
	case UVERBS_OBJECT_CQ:
		return get_enc_obj_id(MLX5_CMD_OP_CREATE_CQ,
				      to_mcq(uobj->object)->mcq.cqn) ==
				      obj_id;

	case UVERBS_OBJECT_SRQ:
	{
		struct mlx5_core_srq *srq = &(to_msrq(uobj->object)->msrq);
		u16 opcode;

		switch (srq->common.res) {
		case MLX5_RES_XSRQ:
			opcode = MLX5_CMD_OP_CREATE_XRC_SRQ;
			break;
		case MLX5_RES_XRQ:
			opcode = MLX5_CMD_OP_CREATE_XRQ;
			break;
		default:
			if (!dev->mdev->issi)
				opcode = MLX5_CMD_OP_CREATE_SRQ;
			else
				opcode = MLX5_CMD_OP_CREATE_RMP;
		}

		return get_enc_obj_id(opcode,
				      to_msrq(uobj->object)->msrq.srqn) ==
				      obj_id;
	}

	case UVERBS_OBJECT_QP:
	{
		struct mlx5_ib_qp *qp = to_mqp(uobj->object);
		enum ib_qp_type	qp_type = qp->ibqp.qp_type;

		if (qp_type == IB_QPT_RAW_PACKET ||
		    (qp->flags & MLX5_IB_QP_UNDERLAY)) {
			struct mlx5_ib_raw_packet_qp *raw_packet_qp =
							 &qp->raw_packet_qp;
			struct mlx5_ib_rq *rq = &raw_packet_qp->rq;
			struct mlx5_ib_sq *sq = &raw_packet_qp->sq;

			return (get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
					       rq->base.mqp.qpn) == obj_id ||
				get_enc_obj_id(MLX5_CMD_OP_CREATE_SQ,
					       sq->base.mqp.qpn) == obj_id ||
				get_enc_obj_id(MLX5_CMD_OP_CREATE_TIR,
					       rq->tirn) == obj_id ||
				get_enc_obj_id(MLX5_CMD_OP_CREATE_TIS,
					       sq->tisn) == obj_id);
		}

		if (qp_type == MLX5_IB_QPT_DCT)
			return get_enc_obj_id(MLX5_CMD_OP_CREATE_DCT,
					      qp->dct.mdct.mqp.qpn) == obj_id;

		return get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
				      qp->ibqp.qp_num) == obj_id;
	}

	case UVERBS_OBJECT_WQ:
		return get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
				      to_mrwq(uobj->object)->core_qp.qpn) ==
				      obj_id;

	case UVERBS_OBJECT_RWQ_IND_TBL:
		return get_enc_obj_id(MLX5_CMD_OP_CREATE_RQT,
				      to_mrwq_ind_table(uobj->object)->rqtn) ==
				      obj_id;

	case MLX5_IB_OBJECT_DEVX_OBJ:
		return ((struct devx_obj *)uobj->object)->obj_id == obj_id;

	default:
		return false;
	}
}
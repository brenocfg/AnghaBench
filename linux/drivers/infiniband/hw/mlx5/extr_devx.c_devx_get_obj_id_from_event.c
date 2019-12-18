#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_7__ {int /*<<< orphan*/  dctn; } ;
struct TYPE_6__ {int /*<<< orphan*/  type_xrqn; } ;
struct TYPE_9__ {int /*<<< orphan*/  qp_srq_n; } ;
struct TYPE_10__ {TYPE_3__ cq_err; TYPE_2__ dct; TYPE_1__ xrq_err; TYPE_4__ qp_srq; } ;
struct mlx5_eqe {TYPE_5__ data; } ;

/* Variables and functions */
#define  MLX5_EVENT_TYPE_COMM_EST 141 
#define  MLX5_EVENT_TYPE_CQ_ERROR 140 
#define  MLX5_EVENT_TYPE_DCT_DRAINED 139 
#define  MLX5_EVENT_TYPE_DCT_KEY_VIOLATION 138 
#define  MLX5_EVENT_TYPE_PATH_MIG 137 
#define  MLX5_EVENT_TYPE_PATH_MIG_FAILED 136 
#define  MLX5_EVENT_TYPE_SQ_DRAINED 135 
#define  MLX5_EVENT_TYPE_SRQ_CATAS_ERROR 134 
#define  MLX5_EVENT_TYPE_SRQ_LAST_WQE 133 
#define  MLX5_EVENT_TYPE_SRQ_RQ_LIMIT 132 
#define  MLX5_EVENT_TYPE_WQ_ACCESS_ERROR 131 
#define  MLX5_EVENT_TYPE_WQ_CATAS_ERROR 130 
#define  MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR 129 
#define  MLX5_EVENT_TYPE_XRQ_ERROR 128 
 int MLX5_GET (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  affiliated_event_header ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 devx_get_obj_id_from_event(unsigned long event_type, void *data)
{
	struct mlx5_eqe *eqe = data;
	u32 obj_id = 0;

	switch (event_type) {
	case MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
	case MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
	case MLX5_EVENT_TYPE_PATH_MIG:
	case MLX5_EVENT_TYPE_COMM_EST:
	case MLX5_EVENT_TYPE_SQ_DRAINED:
	case MLX5_EVENT_TYPE_SRQ_LAST_WQE:
	case MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
	case MLX5_EVENT_TYPE_PATH_MIG_FAILED:
	case MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
	case MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
		obj_id = be32_to_cpu(eqe->data.qp_srq.qp_srq_n) & 0xffffff;
		break;
	case MLX5_EVENT_TYPE_XRQ_ERROR:
		obj_id = be32_to_cpu(eqe->data.xrq_err.type_xrqn) & 0xffffff;
		break;
	case MLX5_EVENT_TYPE_DCT_DRAINED:
	case MLX5_EVENT_TYPE_DCT_KEY_VIOLATION:
		obj_id = be32_to_cpu(eqe->data.dct.dctn) & 0xffffff;
		break;
	case MLX5_EVENT_TYPE_CQ_ERROR:
		obj_id = be32_to_cpu(eqe->data.cq_err.cqn) & 0xffffff;
		break;
	default:
		obj_id = MLX5_GET(affiliated_event_header, &eqe->data, obj_id);
		break;
	}

	return obj_id;
}
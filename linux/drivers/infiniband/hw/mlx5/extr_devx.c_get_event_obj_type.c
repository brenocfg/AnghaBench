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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ qp_srq; } ;
struct mlx5_eqe {TYPE_2__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_EVENT_QUEUE_TYPE_DCT ; 
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
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affiliated_event_header ; 
 int /*<<< orphan*/  obj_type ; 

__attribute__((used)) static u16 get_event_obj_type(unsigned long event_type, struct mlx5_eqe *eqe)
{
	switch (event_type) {
	case MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
	case MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
	case MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
	case MLX5_EVENT_TYPE_SRQ_LAST_WQE:
	case MLX5_EVENT_TYPE_PATH_MIG:
	case MLX5_EVENT_TYPE_PATH_MIG_FAILED:
	case MLX5_EVENT_TYPE_COMM_EST:
	case MLX5_EVENT_TYPE_SQ_DRAINED:
	case MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
	case MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
		return eqe->data.qp_srq.type;
	case MLX5_EVENT_TYPE_CQ_ERROR:
	case MLX5_EVENT_TYPE_XRQ_ERROR:
		return 0;
	case MLX5_EVENT_TYPE_DCT_DRAINED:
	case MLX5_EVENT_TYPE_DCT_KEY_VIOLATION:
		return MLX5_EVENT_QUEUE_TYPE_DCT;
	default:
		return MLX5_GET(affiliated_event_header, &eqe->data, obj_type);
	}
}
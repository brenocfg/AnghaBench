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
typedef  int u32 ;
struct mlx5_core_rsc_common {int res; } ;
struct mlx5_core_qp {int /*<<< orphan*/  (* event ) (struct mlx5_core_qp*,int) ;} ;
struct mlx5_core_dev {int dummy; } ;
struct mlx5_core_dct {int /*<<< orphan*/  drained; } ;

/* Variables and functions */
 int MLX5_EVENT_TYPE_DCT_DRAINED ; 
#define  MLX5_RES_DCT 131 
#define  MLX5_RES_QP 130 
#define  MLX5_RES_RQ 129 
#define  MLX5_RES_SQ 128 
 int MLX5_USER_INDEX_LEN ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_event_type_allowed (int,int) ; 
 int /*<<< orphan*/  mlx5_core_put_rsc (struct mlx5_core_rsc_common*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,...) ; 
 struct mlx5_core_rsc_common* mlx5_get_rsc (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_core_qp*,int) ; 

void mlx5_rsc_event(struct mlx5_core_dev *dev, u32 rsn, int event_type)
{
	struct mlx5_core_rsc_common *common = mlx5_get_rsc(dev, rsn);
	struct mlx5_core_dct *dct;
	struct mlx5_core_qp *qp;

	if (!common)
		return;

	if (!is_event_type_allowed((rsn >> MLX5_USER_INDEX_LEN), event_type)) {
		mlx5_core_warn(dev, "event 0x%.2x is not allowed on resource 0x%.8x\n",
			       event_type, rsn);
		return;
	}

	switch (common->res) {
	case MLX5_RES_QP:
	case MLX5_RES_RQ:
	case MLX5_RES_SQ:
		qp = (struct mlx5_core_qp *)common;
		qp->event(qp, event_type);
		break;
	case MLX5_RES_DCT:
		dct = (struct mlx5_core_dct *)common;
		if (event_type == MLX5_EVENT_TYPE_DCT_DRAINED)
			complete(&dct->drained);
		break;
	default:
		mlx5_core_warn(dev, "invalid resource type for 0x%x\n", rsn);
	}

	mlx5_core_put_rsc(common);
}
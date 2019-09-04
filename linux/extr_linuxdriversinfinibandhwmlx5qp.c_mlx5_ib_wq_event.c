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
struct TYPE_4__ {int /*<<< orphan*/  wq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct mlx5_ib_rwq {TYPE_2__ ibwq; } ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_core_qp {int /*<<< orphan*/  qpn; } ;
struct TYPE_3__ {TYPE_2__* wq; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_WQ_FATAL ; 
#define  MLX5_EVENT_TYPE_WQ_CATAS_ERROR 128 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_rwq* to_mibrwq (struct mlx5_core_qp*) ; 

__attribute__((used)) static void mlx5_ib_wq_event(struct mlx5_core_qp *core_qp, int type)
{
	struct mlx5_ib_rwq *rwq = to_mibrwq(core_qp);
	struct mlx5_ib_dev *dev = to_mdev(rwq->ibwq.device);
	struct ib_event event;

	if (rwq->ibwq.event_handler) {
		event.device     = rwq->ibwq.device;
		event.element.wq = &rwq->ibwq;
		switch (type) {
		case MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
			event.event = IB_EVENT_WQ_FATAL;
			break;
		default:
			mlx5_ib_warn(dev, "Unexpected event type %d on WQ %06x\n", type, core_qp->qpn);
			return;
		}

		rwq->ibwq.event_handler(&event, rwq->ibwq.wq_context);
	}
}
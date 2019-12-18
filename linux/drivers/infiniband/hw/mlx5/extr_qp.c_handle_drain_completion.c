#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_ib_drain_cqe {int /*<<< orphan*/  done; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  reset_flow_resource_lock; struct mlx5_core_dev* mdev; } ;
struct TYPE_2__ {int reset_notify_added; int /*<<< orphan*/  (* comp ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct mlx5_ib_cq {TYPE_1__ mcq; } ;
struct mlx5_core_dev {scalar_t__ state; } ;
struct ib_cq {int poll_ctx; int /*<<< orphan*/  work; int /*<<< orphan*/  iop; } ;

/* Variables and functions */
 int HZ ; 
 int IB_POLL_DIRECT ; 
#define  IB_POLL_SOFTIRQ 129 
#define  IB_POLL_WORKQUEUE 128 
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_process_cq_direct (struct ib_cq*,int) ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_poll_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_cq* to_mcq (struct ib_cq*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void handle_drain_completion(struct ib_cq *cq,
				    struct mlx5_ib_drain_cqe *sdrain,
				    struct mlx5_ib_dev *dev)
{
	struct mlx5_core_dev *mdev = dev->mdev;

	if (cq->poll_ctx == IB_POLL_DIRECT) {
		while (wait_for_completion_timeout(&sdrain->done, HZ / 10) <= 0)
			ib_process_cq_direct(cq, -1);
		return;
	}

	if (mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) {
		struct mlx5_ib_cq *mcq = to_mcq(cq);
		bool triggered = false;
		unsigned long flags;

		spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
		/* Make sure that the CQ handler won't run if wasn't run yet */
		if (!mcq->mcq.reset_notify_added)
			mcq->mcq.reset_notify_added = 1;
		else
			triggered = true;
		spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);

		if (triggered) {
			/* Wait for any scheduled/running task to be ended */
			switch (cq->poll_ctx) {
			case IB_POLL_SOFTIRQ:
				irq_poll_disable(&cq->iop);
				irq_poll_enable(&cq->iop);
				break;
			case IB_POLL_WORKQUEUE:
				cancel_work_sync(&cq->work);
				break;
			default:
				WARN_ON_ONCE(1);
			}
		}

		/* Run the CQ handler - this makes sure that the drain WR will
		 * be processed if wasn't processed yet.
		 */
		mcq->mcq.comp(&mcq->mcq, NULL);
	}

	wait_for_completion(&sdrain->done);
}
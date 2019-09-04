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
struct mlx4_srq {int /*<<< orphan*/  srqn; } ;
struct ib_srq {int /*<<< orphan*/  srq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct TYPE_3__ {struct ib_srq* srq; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/  device; } ;
typedef  enum mlx4_event { ____Placeholder_mlx4_event } mlx4_event ;
struct TYPE_4__ {struct ib_srq ibsrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_SRQ_ERR ; 
 int /*<<< orphan*/  IB_EVENT_SRQ_LIMIT_REACHED ; 
#define  MLX4_EVENT_TYPE_SRQ_CATAS_ERROR 129 
#define  MLX4_EVENT_TYPE_SRQ_LIMIT 128 
 int /*<<< orphan*/  pr_warn (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mibsrq (struct mlx4_srq*) ; 

__attribute__((used)) static void mlx4_ib_srq_event(struct mlx4_srq *srq, enum mlx4_event type)
{
	struct ib_event event;
	struct ib_srq *ibsrq = &to_mibsrq(srq)->ibsrq;

	if (ibsrq->event_handler) {
		event.device      = ibsrq->device;
		event.element.srq = ibsrq;
		switch (type) {
		case MLX4_EVENT_TYPE_SRQ_LIMIT:
			event.event = IB_EVENT_SRQ_LIMIT_REACHED;
			break;
		case MLX4_EVENT_TYPE_SRQ_CATAS_ERROR:
			event.event = IB_EVENT_SRQ_ERR;
			break;
		default:
			pr_warn("Unexpected event type %d "
			       "on SRQ %06x\n", type, srq->srqn);
			return;
		}

		ibsrq->event_handler(&event, ibsrq->srq_context);
	}
}
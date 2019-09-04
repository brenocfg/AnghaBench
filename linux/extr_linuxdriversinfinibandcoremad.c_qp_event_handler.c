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
struct ib_mad_qp_info {TYPE_3__* qp; TYPE_2__* port_priv; } ;
struct ib_event {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {int /*<<< orphan*/  qp_num; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qp_event_handler(struct ib_event *event, void *qp_context)
{
	struct ib_mad_qp_info	*qp_info = qp_context;

	/* It's worse than that! He's dead, Jim! */
	dev_err(&qp_info->port_priv->device->dev,
		"Fatal error (%d) on MAD QP (%d)\n",
		event->event, qp_info->qp->qp_num);
}
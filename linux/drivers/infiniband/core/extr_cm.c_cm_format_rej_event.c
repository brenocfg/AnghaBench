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
struct ib_cm_rej_event_param {int /*<<< orphan*/  reason; int /*<<< orphan*/  ari_length; int /*<<< orphan*/  ari; } ;
struct TYPE_8__ {struct ib_cm_rej_event_param rej_rcvd; } ;
struct TYPE_7__ {int /*<<< orphan*/ * private_data; TYPE_4__ param; } ;
struct cm_work {TYPE_3__ cm_event; TYPE_2__* mad_recv_wc; } ;
struct cm_rej_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  reason; int /*<<< orphan*/  ari; } ;
struct TYPE_5__ {scalar_t__ mad; } ;
struct TYPE_6__ {TYPE_1__ recv_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  __be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rej_get_reject_info_len (struct cm_rej_msg*) ; 

__attribute__((used)) static void cm_format_rej_event(struct cm_work *work)
{
	struct cm_rej_msg *rej_msg;
	struct ib_cm_rej_event_param *param;

	rej_msg = (struct cm_rej_msg *)work->mad_recv_wc->recv_buf.mad;
	param = &work->cm_event.param.rej_rcvd;
	param->ari = rej_msg->ari;
	param->ari_length = cm_rej_get_reject_info_len(rej_msg);
	param->reason = __be16_to_cpu(rej_msg->reason);
	work->cm_event.private_data = &rej_msg->private_data;
}
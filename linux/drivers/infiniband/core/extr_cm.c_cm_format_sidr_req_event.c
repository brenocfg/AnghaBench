#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ib_cm_sidr_req_event_param {int /*<<< orphan*/  sgid_attr; int /*<<< orphan*/  port; int /*<<< orphan*/  bth_pkey; int /*<<< orphan*/  service_id; struct ib_cm_id* listen_id; int /*<<< orphan*/  pkey; } ;
struct ib_cm_id {int dummy; } ;
struct TYPE_11__ {struct ib_cm_sidr_req_event_param sidr_req_rcvd; } ;
struct TYPE_16__ {int /*<<< orphan*/ * private_data; TYPE_3__ param; } ;
struct cm_work {TYPE_8__ cm_event; TYPE_4__* port; TYPE_2__* mad_recv_wc; } ;
struct cm_sidr_req_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  service_id; int /*<<< orphan*/  pkey; } ;
struct TYPE_13__ {int /*<<< orphan*/  sgid_attr; } ;
struct TYPE_14__ {TYPE_5__ grh; } ;
struct TYPE_15__ {TYPE_6__ ah_attr; } ;
struct cm_id_private {TYPE_7__ av; } ;
struct TYPE_12__ {int /*<<< orphan*/  port_num; } ;
struct TYPE_9__ {scalar_t__ mad; } ;
struct TYPE_10__ {TYPE_1__ recv_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  __be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_get_bth_pkey (struct cm_work*) ; 

__attribute__((used)) static void cm_format_sidr_req_event(struct cm_work *work,
				     const struct cm_id_private *rx_cm_id,
				     struct ib_cm_id *listen_id)
{
	struct cm_sidr_req_msg *sidr_req_msg;
	struct ib_cm_sidr_req_event_param *param;

	sidr_req_msg = (struct cm_sidr_req_msg *)
				work->mad_recv_wc->recv_buf.mad;
	param = &work->cm_event.param.sidr_req_rcvd;
	param->pkey = __be16_to_cpu(sidr_req_msg->pkey);
	param->listen_id = listen_id;
	param->service_id = sidr_req_msg->service_id;
	param->bth_pkey = cm_get_bth_pkey(work);
	param->port = work->port->port_num;
	param->sgid_attr = rx_cm_id->av.ah_attr.grh.sgid_attr;
	work->cm_event.private_data = &sidr_req_msg->private_data;
}
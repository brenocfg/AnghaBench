#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct qedr_iw_listener {TYPE_1__* cm_id; struct qedr_dev* dev; } ;
struct qedr_iw_ep {int /*<<< orphan*/  qed_context; struct qedr_dev* dev; } ;
struct qedr_dev {int dummy; } ;
struct qed_iwarp_cm_event_params {TYPE_2__* cm_info; int /*<<< orphan*/  status; int /*<<< orphan*/  ep_context; } ;
struct iw_cm_event {int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; scalar_t__ private_data_len; void* private_data; void* provider_data; int /*<<< orphan*/  status; int /*<<< orphan*/  event; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_5__ {scalar_t__ ip_version; int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; scalar_t__ private_data_len; scalar_t__ private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*,struct iw_cm_event*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IPV6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IW_CM_EVENT_CONNECT_REQUEST ; 
 scalar_t__ QED_TCP_IPV4 ; 
 struct qedr_iw_ep* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iw_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedr_fill_sockaddr4 (TYPE_2__*,struct iw_cm_event*) ; 
 int /*<<< orphan*/  qedr_fill_sockaddr6 (TYPE_2__*,struct iw_cm_event*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct iw_cm_event*) ; 

__attribute__((used)) static void
qedr_iw_mpa_request(void *context, struct qed_iwarp_cm_event_params *params)
{
	struct qedr_iw_listener *listener = (struct qedr_iw_listener *)context;
	struct qedr_dev *dev = listener->dev;
	struct iw_cm_event event;
	struct qedr_iw_ep *ep;

	ep = kzalloc(sizeof(*ep), GFP_ATOMIC);
	if (!ep)
		return;

	ep->dev = dev;
	ep->qed_context = params->ep_context;

	memset(&event, 0, sizeof(event));
	event.event = IW_CM_EVENT_CONNECT_REQUEST;
	event.status = params->status;

	if (!IS_ENABLED(CONFIG_IPV6) ||
	    params->cm_info->ip_version == QED_TCP_IPV4)
		qedr_fill_sockaddr4(params->cm_info, &event);
	else
		qedr_fill_sockaddr6(params->cm_info, &event);

	event.provider_data = (void *)ep;
	event.private_data = (void *)params->cm_info->private_data;
	event.private_data_len = (u8)params->cm_info->private_data_len;
	event.ord = params->cm_info->ord;
	event.ird = params->cm_info->ird;

	listener->cm_id->event_handler(listener->cm_id, &event);
}
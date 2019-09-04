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
typedef  int /*<<< orphan*/  u8 ;
struct iw_cm_id {int (* event_handler ) (struct iw_cm_id*,struct iw_cm_event*) ;} ;
struct iw_cm_event {int event; int status; int /*<<< orphan*/  ord; int /*<<< orphan*/  ird; int /*<<< orphan*/  private_data_len; void* private_data; void* provider_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct i40iw_cm_node {int /*<<< orphan*/  ord_size; int /*<<< orphan*/  ird_size; TYPE_1__ pdata; scalar_t__ pdata_buf; int /*<<< orphan*/  ipv4; } ;
typedef  int /*<<< orphan*/  event ;
typedef  enum iw_cm_event_type { ____Placeholder_iw_cm_event_type } iw_cm_event_type ;

/* Variables and functions */
#define  IW_CM_EVENT_CLOSE 132 
#define  IW_CM_EVENT_CONNECT_REPLY 131 
#define  IW_CM_EVENT_CONNECT_REQUEST 130 
#define  IW_CM_EVENT_DISCONNECT 129 
#define  IW_CM_EVENT_ESTABLISHED 128 
 int /*<<< orphan*/  i40iw_fill_sockaddr4 (struct i40iw_cm_node*,struct iw_cm_event*) ; 
 int /*<<< orphan*/  i40iw_fill_sockaddr6 (struct i40iw_cm_node*,struct iw_cm_event*) ; 
 int /*<<< orphan*/  i40iw_get_cmevent_info (struct i40iw_cm_node*,struct iw_cm_id*,struct iw_cm_event*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,int) ; 
 int /*<<< orphan*/  memset (struct iw_cm_event*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct iw_cm_id*,struct iw_cm_event*) ; 

__attribute__((used)) static int i40iw_send_cm_event(struct i40iw_cm_node *cm_node,
			       struct iw_cm_id *cm_id,
			       enum iw_cm_event_type type,
			       int status)
{
	struct iw_cm_event event;

	memset(&event, 0, sizeof(event));
	event.event = type;
	event.status = status;
	switch (type) {
	case IW_CM_EVENT_CONNECT_REQUEST:
		if (cm_node->ipv4)
			i40iw_fill_sockaddr4(cm_node, &event);
		else
			i40iw_fill_sockaddr6(cm_node, &event);
		event.provider_data = (void *)cm_node;
		event.private_data = (void *)cm_node->pdata_buf;
		event.private_data_len = (u8)cm_node->pdata.size;
		event.ird = cm_node->ird_size;
		break;
	case IW_CM_EVENT_CONNECT_REPLY:
		i40iw_get_cmevent_info(cm_node, cm_id, &event);
		break;
	case IW_CM_EVENT_ESTABLISHED:
		event.ird = cm_node->ird_size;
		event.ord = cm_node->ord_size;
		break;
	case IW_CM_EVENT_DISCONNECT:
		break;
	case IW_CM_EVENT_CLOSE:
		break;
	default:
		i40iw_pr_err("event type received type = %d\n", type);
		return -1;
	}
	return cm_id->event_handler(cm_id, &event);
}
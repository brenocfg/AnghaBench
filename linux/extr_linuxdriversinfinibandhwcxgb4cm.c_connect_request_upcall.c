#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mpa_v2_conn_params {int dummy; } ;
struct mpa_message {int dummy; } ;
struct iw_cm_event {scalar_t__ private_data; scalar_t__ private_data_len; void* ird; void* ord; struct c4iw_ep* provider_data; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  event; } ;
struct TYPE_7__ {int /*<<< orphan*/  history; TYPE_2__* cm_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct c4iw_ep {TYPE_1__* parent_ep; TYPE_3__ com; scalar_t__ mpa_pkt; scalar_t__ plen; void* ird; void* ord; int /*<<< orphan*/  tried_with_mpa_v1; int /*<<< orphan*/  hwtid; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_6__ {int (* event_handler ) (TYPE_2__*,struct iw_cm_event*) ;} ;
struct TYPE_5__ {TYPE_3__ com; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNREQ_UPCALL ; 
 int /*<<< orphan*/  IW_CM_EVENT_CONNECT_REQUEST ; 
 int /*<<< orphan*/  c4iw_get_ep (TYPE_3__*) ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_3__*) ; 
 void* cur_max_read_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct iw_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,struct iw_cm_event*) ; 

__attribute__((used)) static int connect_request_upcall(struct c4iw_ep *ep)
{
	struct iw_cm_event event;
	int ret;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	memset(&event, 0, sizeof(event));
	event.event = IW_CM_EVENT_CONNECT_REQUEST;
	memcpy(&event.local_addr, &ep->com.local_addr,
	       sizeof(ep->com.local_addr));
	memcpy(&event.remote_addr, &ep->com.remote_addr,
	       sizeof(ep->com.remote_addr));
	event.provider_data = ep;
	if (!ep->tried_with_mpa_v1) {
		/* this means MPA_v2 is used */
		event.ord = ep->ord;
		event.ird = ep->ird;
		event.private_data_len = ep->plen -
			sizeof(struct mpa_v2_conn_params);
		event.private_data = ep->mpa_pkt + sizeof(struct mpa_message) +
			sizeof(struct mpa_v2_conn_params);
	} else {
		/* this means MPA_v1 is used. Send max supported */
		event.ord = cur_max_read_depth(ep->com.dev);
		event.ird = cur_max_read_depth(ep->com.dev);
		event.private_data_len = ep->plen;
		event.private_data = ep->mpa_pkt + sizeof(struct mpa_message);
	}
	c4iw_get_ep(&ep->com);
	ret = ep->parent_ep->com.cm_id->event_handler(ep->parent_ep->com.cm_id,
						      &event);
	if (ret)
		c4iw_put_ep(&ep->com);
	set_bit(CONNREQ_UPCALL, &ep->com.history);
	c4iw_put_ep(&ep->parent_ep->com);
	return ret;
}
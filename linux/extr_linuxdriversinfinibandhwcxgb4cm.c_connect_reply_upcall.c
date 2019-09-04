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
struct mpa_v2_conn_params {int dummy; } ;
struct mpa_message {int dummy; } ;
struct iw_cm_event {int status; scalar_t__ private_data; scalar_t__ private_data_len; void* ird; void* ord; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  event; } ;
struct TYPE_4__ {TYPE_1__* cm_id; int /*<<< orphan*/  history; int /*<<< orphan*/  dev; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct c4iw_ep {TYPE_2__ com; int /*<<< orphan*/  hwtid; scalar_t__ mpa_pkt; scalar_t__ plen; void* ord; void* ird; int /*<<< orphan*/  tried_with_mpa_v1; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_3__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*,struct iw_cm_event*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_RPL_UPCALL ; 
 int ECONNREFUSED ; 
 int /*<<< orphan*/  IW_CM_EVENT_CONNECT_REPLY ; 
 void* cur_max_read_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deref_cm_id (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct iw_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct iw_cm_event*) ; 

__attribute__((used)) static void connect_reply_upcall(struct c4iw_ep *ep, int status)
{
	struct iw_cm_event event;

	pr_debug("ep %p tid %u status %d\n",
		 ep, ep->hwtid, status);
	memset(&event, 0, sizeof(event));
	event.event = IW_CM_EVENT_CONNECT_REPLY;
	event.status = status;
	memcpy(&event.local_addr, &ep->com.local_addr,
	       sizeof(ep->com.local_addr));
	memcpy(&event.remote_addr, &ep->com.remote_addr,
	       sizeof(ep->com.remote_addr));

	if ((status == 0) || (status == -ECONNREFUSED)) {
		if (!ep->tried_with_mpa_v1) {
			/* this means MPA_v2 is used */
			event.ord = ep->ird;
			event.ird = ep->ord;
			event.private_data_len = ep->plen -
				sizeof(struct mpa_v2_conn_params);
			event.private_data = ep->mpa_pkt +
				sizeof(struct mpa_message) +
				sizeof(struct mpa_v2_conn_params);
		} else {
			/* this means MPA_v1 is used */
			event.ord = cur_max_read_depth(ep->com.dev);
			event.ird = cur_max_read_depth(ep->com.dev);
			event.private_data_len = ep->plen;
			event.private_data = ep->mpa_pkt +
				sizeof(struct mpa_message);
		}
	}

	pr_debug("ep %p tid %u status %d\n", ep,
		 ep->hwtid, status);
	set_bit(CONN_RPL_UPCALL, &ep->com.history);
	ep->com.cm_id->event_handler(ep->com.cm_id, &event);

	if (status < 0)
		deref_cm_id(&ep->com);
}
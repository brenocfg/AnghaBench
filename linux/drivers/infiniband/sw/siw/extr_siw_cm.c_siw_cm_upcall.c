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
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  pd_len; } ;
struct TYPE_7__ {TYPE_2__ params; } ;
struct TYPE_8__ {int pdata; TYPE_3__ hdr; } ;
struct siw_cep {scalar_t__ qp; int /*<<< orphan*/  sock; scalar_t__ enhanced_rdma_conn_est; TYPE_4__ mpa; int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; struct iw_cm_id* cm_id; TYPE_1__* listen_cep; } ;
struct mpa_v2_data {int dummy; } ;
struct iw_cm_id {int (* event_handler ) (struct iw_cm_id*,struct iw_cm_event*) ;} ;
struct iw_cm_event {int status; int event; int private_data; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; scalar_t__ private_data_len; int /*<<< orphan*/  ord; int /*<<< orphan*/  ird; struct siw_cep* provider_data; } ;
typedef  int /*<<< orphan*/  event ;
typedef  enum iw_cm_event_type { ____Placeholder_iw_cm_event_type } iw_cm_event_type ;
struct TYPE_5__ {struct iw_cm_id* cm_id; } ;

/* Variables and functions */
 int IW_CM_EVENT_CONNECT_REPLY ; 
 int IW_CM_EVENT_CONNECT_REQUEST ; 
 int IW_CM_EVENT_ESTABLISHED ; 
 int /*<<< orphan*/  UINT_MAX ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getname_local (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getname_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct iw_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qp_id (scalar_t__) ; 
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (struct iw_cm_id*,struct iw_cm_event*) ; 

__attribute__((used)) static int siw_cm_upcall(struct siw_cep *cep, enum iw_cm_event_type reason,
			 int status)
{
	struct iw_cm_event event;
	struct iw_cm_id *id;

	memset(&event, 0, sizeof(event));
	event.status = status;
	event.event = reason;

	if (reason == IW_CM_EVENT_CONNECT_REQUEST) {
		event.provider_data = cep;
		id = cep->listen_cep->cm_id;
	} else {
		id = cep->cm_id;
	}
	/* Signal IRD and ORD */
	if (reason == IW_CM_EVENT_ESTABLISHED ||
	    reason == IW_CM_EVENT_CONNECT_REPLY) {
		/* Signal negotiated IRD/ORD values we will use */
		event.ird = cep->ird;
		event.ord = cep->ord;
	} else if (reason == IW_CM_EVENT_CONNECT_REQUEST) {
		event.ird = cep->ord;
		event.ord = cep->ird;
	}
	/* Signal private data and address information */
	if (reason == IW_CM_EVENT_CONNECT_REQUEST ||
	    reason == IW_CM_EVENT_CONNECT_REPLY) {
		u16 pd_len = be16_to_cpu(cep->mpa.hdr.params.pd_len);

		if (pd_len) {
			/*
			 * hand over MPA private data
			 */
			event.private_data_len = pd_len;
			event.private_data = cep->mpa.pdata;

			/* Hide MPA V2 IRD/ORD control */
			if (cep->enhanced_rdma_conn_est) {
				event.private_data_len -=
					sizeof(struct mpa_v2_data);
				event.private_data +=
					sizeof(struct mpa_v2_data);
			}
		}
		getname_local(cep->sock, &event.local_addr);
		getname_peer(cep->sock, &event.remote_addr);
	}
	siw_dbg_cep(cep, "[QP %u]: reason=%d, status=%d\n",
		    cep->qp ? qp_id(cep->qp) : UINT_MAX, reason, status);

	return id->event_handler(id, &event);
}
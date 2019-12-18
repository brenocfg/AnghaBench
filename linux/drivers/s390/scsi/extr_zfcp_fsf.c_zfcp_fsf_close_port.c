#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct zfcp_qdio {int /*<<< orphan*/  req_q_lock; TYPE_3__* adapter; } ;
struct zfcp_fsf_req {int /*<<< orphan*/  req_id; TYPE_5__* qtcb; struct zfcp_erp_action* erp_action; TYPE_6__* data; int /*<<< orphan*/  handler; int /*<<< orphan*/  qdio_req; int /*<<< orphan*/  status; } ;
struct zfcp_erp_action {int /*<<< orphan*/  fsf_req_id; TYPE_6__* port; TYPE_1__* adapter; } ;
struct TYPE_12__ {int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {int /*<<< orphan*/  port_handle; } ;
struct TYPE_11__ {TYPE_4__ header; } ;
struct TYPE_8__ {int /*<<< orphan*/  erp_req; } ;
struct TYPE_9__ {TYPE_2__ pool; } ;
struct TYPE_7__ {struct zfcp_qdio* qdio; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FSF_QTCB_CLOSE_PORT ; 
 scalar_t__ IS_ERR (struct zfcp_fsf_req*) ; 
 int PTR_ERR (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_READ ; 
 int /*<<< orphan*/  ZFCP_STATUS_FSFREQ_CLEANUP ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fsf_close_port_handler ; 
 struct zfcp_fsf_req* zfcp_fsf_req_create (struct zfcp_qdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 int zfcp_fsf_req_send (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_start_erp_timer (struct zfcp_fsf_req*) ; 
 scalar_t__ zfcp_qdio_sbal_get (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  zfcp_qdio_set_sbale_last (struct zfcp_qdio*,int /*<<< orphan*/ *) ; 

int zfcp_fsf_close_port(struct zfcp_erp_action *erp_action)
{
	struct zfcp_qdio *qdio = erp_action->adapter->qdio;
	struct zfcp_fsf_req *req;
	int retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	if (zfcp_qdio_sbal_get(qdio))
		goto out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_CLOSE_PORT,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.erp_req);

	if (IS_ERR(req)) {
		retval = PTR_ERR(req);
		goto out;
	}

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->handler = zfcp_fsf_close_port_handler;
	req->data = erp_action->port;
	req->erp_action = erp_action;
	req->qtcb->header.port_handle = erp_action->port->handle;
	erp_action->fsf_req_id = req->req_id;

	zfcp_fsf_start_erp_timer(req);
	retval = zfcp_fsf_req_send(req);
	if (retval) {
		zfcp_fsf_req_free(req);
		erp_action->fsf_req_id = 0;
	}
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	return retval;
}
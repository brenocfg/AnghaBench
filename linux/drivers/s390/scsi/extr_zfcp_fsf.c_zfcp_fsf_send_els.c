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
typedef  int /*<<< orphan*/  u32 ;
struct zfcp_qdio {int /*<<< orphan*/  req_q_lock; } ;
struct zfcp_fsf_req {struct zfcp_fsf_ct_els* data; int /*<<< orphan*/  handler; TYPE_3__* qtcb; int /*<<< orphan*/  qdio_req; int /*<<< orphan*/  status; } ;
struct zfcp_fsf_ct_els {int /*<<< orphan*/  d_id; int /*<<< orphan*/  resp; int /*<<< orphan*/  req; } ;
struct zfcp_adapter {struct zfcp_qdio* qdio; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_id; } ;
struct TYPE_5__ {TYPE_1__ support; } ;
struct TYPE_6__ {TYPE_2__ bottom; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FSF_QTCB_SEND_ELS ; 
 scalar_t__ IS_ERR (struct zfcp_fsf_req*) ; 
 int PTR_ERR (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_WRITE_READ ; 
 int /*<<< orphan*/  ZFCP_STATUS_FSFREQ_CLEANUP ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_adapter_multi_buffer_active (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_dbf_san_req (char*,struct zfcp_fsf_req*,int /*<<< orphan*/ ) ; 
 struct zfcp_fsf_req* zfcp_fsf_req_create (struct zfcp_qdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 int zfcp_fsf_req_send (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_send_els_handler ; 
 int zfcp_fsf_setup_ct_els (struct zfcp_fsf_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ zfcp_qdio_sbal_get (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  zfcp_qdio_sbal_limit (struct zfcp_qdio*,int /*<<< orphan*/ *,int) ; 

int zfcp_fsf_send_els(struct zfcp_adapter *adapter, u32 d_id,
		      struct zfcp_fsf_ct_els *els, unsigned int timeout)
{
	struct zfcp_fsf_req *req;
	struct zfcp_qdio *qdio = adapter->qdio;
	int ret = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	if (zfcp_qdio_sbal_get(qdio))
		goto out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_SEND_ELS,
				  SBAL_SFLAGS0_TYPE_WRITE_READ, NULL);

	if (IS_ERR(req)) {
		ret = PTR_ERR(req);
		goto out;
	}

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;

	if (!zfcp_adapter_multi_buffer_active(adapter))
		zfcp_qdio_sbal_limit(qdio, &req->qdio_req, 2);

	ret = zfcp_fsf_setup_ct_els(req, els->req, els->resp, timeout);

	if (ret)
		goto failed_send;

	hton24(req->qtcb->bottom.support.d_id, d_id);
	req->handler = zfcp_fsf_send_els_handler;
	els->d_id = d_id;
	req->data = els;

	zfcp_dbf_san_req("fssels1", req, d_id);

	ret = zfcp_fsf_req_send(req);
	if (ret)
		goto failed_send;
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */

	goto out;

failed_send:
	zfcp_fsf_req_free(req);
out:
	spin_unlock_irq(&qdio->req_q_lock);
	return ret;
}
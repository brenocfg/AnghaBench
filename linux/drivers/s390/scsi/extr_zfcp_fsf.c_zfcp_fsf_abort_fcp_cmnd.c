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
typedef  scalar_t__ u64 ;
struct zfcp_scsi_dev {TYPE_5__* port; int /*<<< orphan*/  lun_handle; int /*<<< orphan*/  status; } ;
struct zfcp_qdio {int /*<<< orphan*/  req_q_lock; TYPE_3__* adapter; } ;
struct zfcp_fsf_req {TYPE_8__* qtcb; int /*<<< orphan*/  handler; struct scsi_device* data; int /*<<< orphan*/  qdio_req; } ;
struct scsi_device {int dummy; } ;
struct scsi_cmnd {scalar_t__ host_scribble; struct scsi_device* device; } ;
struct TYPE_14__ {scalar_t__ req_handle; } ;
struct TYPE_15__ {TYPE_6__ support; } ;
struct TYPE_12__ {int /*<<< orphan*/  port_handle; int /*<<< orphan*/  lun_handle; } ;
struct TYPE_16__ {TYPE_7__ bottom; TYPE_4__ header; } ;
struct TYPE_13__ {int /*<<< orphan*/  handle; TYPE_1__* adapter; } ;
struct TYPE_10__ {int /*<<< orphan*/  scsi_abort; } ;
struct TYPE_11__ {TYPE_2__ pool; } ;
struct TYPE_9__ {struct zfcp_qdio* qdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSF_QTCB_ABORT_FCP_CMND ; 
 scalar_t__ IS_ERR (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_READ ; 
 int /*<<< orphan*/  ZFCP_FSF_SCSI_ER_TIMEOUT ; 
 int ZFCP_STATUS_COMMON_UNBLOCKED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_fsf_abort_fcp_command_handler ; 
 struct zfcp_fsf_req* zfcp_fsf_req_create (struct zfcp_qdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_req_send (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_start_timer (struct zfcp_fsf_req*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfcp_qdio_sbal_get (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  zfcp_qdio_set_sbale_last (struct zfcp_qdio*,int /*<<< orphan*/ *) ; 

struct zfcp_fsf_req *zfcp_fsf_abort_fcp_cmnd(struct scsi_cmnd *scmnd)
{
	struct zfcp_fsf_req *req = NULL;
	struct scsi_device *sdev = scmnd->device;
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	struct zfcp_qdio *qdio = zfcp_sdev->port->adapter->qdio;
	unsigned long old_req_id = (unsigned long) scmnd->host_scribble;

	spin_lock_irq(&qdio->req_q_lock);
	if (zfcp_qdio_sbal_get(qdio))
		goto out;
	req = zfcp_fsf_req_create(qdio, FSF_QTCB_ABORT_FCP_CMND,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.scsi_abort);
	if (IS_ERR(req)) {
		req = NULL;
		goto out;
	}

	if (unlikely(!(atomic_read(&zfcp_sdev->status) &
		       ZFCP_STATUS_COMMON_UNBLOCKED)))
		goto out_error_free;

	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->data = sdev;
	req->handler = zfcp_fsf_abort_fcp_command_handler;
	req->qtcb->header.lun_handle = zfcp_sdev->lun_handle;
	req->qtcb->header.port_handle = zfcp_sdev->port->handle;
	req->qtcb->bottom.support.req_handle = (u64) old_req_id;

	zfcp_fsf_start_timer(req, ZFCP_FSF_SCSI_ER_TIMEOUT);
	if (!zfcp_fsf_req_send(req)) {
		/* NOTE: DO NOT TOUCH req, UNTIL IT COMPLETES! */
		goto out;
	}

out_error_free:
	zfcp_fsf_req_free(req);
	req = NULL;
out:
	spin_unlock_irq(&qdio->req_q_lock);
	return req;
}
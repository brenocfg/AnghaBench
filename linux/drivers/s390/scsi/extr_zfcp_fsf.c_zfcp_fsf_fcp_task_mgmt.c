#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct zfcp_scsi_dev {TYPE_5__* port; int /*<<< orphan*/  lun_handle; int /*<<< orphan*/  status; } ;
struct zfcp_qdio {int /*<<< orphan*/  req_q_lock; TYPE_3__* adapter; } ;
struct zfcp_fsf_req {TYPE_9__* qtcb; int /*<<< orphan*/  qdio_req; int /*<<< orphan*/  handler; struct scsi_device* data; } ;
struct scsi_device {int dummy; } ;
struct fcp_cmnd {int dummy; } ;
struct TYPE_15__ {struct fcp_cmnd iu; } ;
struct TYPE_16__ {TYPE_6__ fcp_cmnd; int /*<<< orphan*/  fcp_cmnd_length; int /*<<< orphan*/  service_class; int /*<<< orphan*/  data_direction; } ;
struct TYPE_17__ {TYPE_7__ io; } ;
struct TYPE_13__ {int /*<<< orphan*/  port_handle; int /*<<< orphan*/  lun_handle; } ;
struct TYPE_18__ {TYPE_8__ bottom; TYPE_4__ header; } ;
struct TYPE_14__ {int /*<<< orphan*/  handle; TYPE_1__* adapter; } ;
struct TYPE_11__ {int /*<<< orphan*/  scsi_req; } ;
struct TYPE_12__ {TYPE_2__ pool; } ;
struct TYPE_10__ {struct zfcp_qdio* qdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCP_CMND_LEN ; 
 int /*<<< orphan*/  FSF_CLASS_3 ; 
 int /*<<< orphan*/  FSF_DATADIR_CMND ; 
 int /*<<< orphan*/  FSF_QTCB_FCP_CMND ; 
 scalar_t__ IS_ERR (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_WRITE ; 
 int /*<<< orphan*/  ZFCP_FSF_SCSI_ER_TIMEOUT ; 
 int ZFCP_STATUS_COMMON_UNBLOCKED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_fc_fcp_tm (struct fcp_cmnd*,struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_fcp_task_mgmt_handler ; 
 struct zfcp_fsf_req* zfcp_fsf_req_create (struct zfcp_qdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_req_send (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_start_timer (struct zfcp_fsf_req*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfcp_qdio_sbal_get (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  zfcp_qdio_set_sbale_last (struct zfcp_qdio*,int /*<<< orphan*/ *) ; 

struct zfcp_fsf_req *zfcp_fsf_fcp_task_mgmt(struct scsi_device *sdev,
					    u8 tm_flags)
{
	struct zfcp_fsf_req *req = NULL;
	struct fcp_cmnd *fcp_cmnd;
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	struct zfcp_qdio *qdio = zfcp_sdev->port->adapter->qdio;

	if (unlikely(!(atomic_read(&zfcp_sdev->status) &
		       ZFCP_STATUS_COMMON_UNBLOCKED)))
		return NULL;

	spin_lock_irq(&qdio->req_q_lock);
	if (zfcp_qdio_sbal_get(qdio))
		goto out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_FCP_CMND,
				  SBAL_SFLAGS0_TYPE_WRITE,
				  qdio->adapter->pool.scsi_req);

	if (IS_ERR(req)) {
		req = NULL;
		goto out;
	}

	req->data = sdev;

	req->handler = zfcp_fsf_fcp_task_mgmt_handler;
	req->qtcb->header.lun_handle = zfcp_sdev->lun_handle;
	req->qtcb->header.port_handle = zfcp_sdev->port->handle;
	req->qtcb->bottom.io.data_direction = FSF_DATADIR_CMND;
	req->qtcb->bottom.io.service_class = FSF_CLASS_3;
	req->qtcb->bottom.io.fcp_cmnd_length = FCP_CMND_LEN;

	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	fcp_cmnd = &req->qtcb->bottom.io.fcp_cmnd.iu;
	zfcp_fc_fcp_tm(fcp_cmnd, sdev, tm_flags);

	zfcp_fsf_start_timer(req, ZFCP_FSF_SCSI_ER_TIMEOUT);
	if (!zfcp_fsf_req_send(req)) {
		/* NOTE: DO NOT TOUCH req, UNTIL IT COMPLETES! */
		goto out;
	}

	zfcp_fsf_req_free(req);
	req = NULL;
out:
	spin_unlock_irq(&qdio->req_q_lock);
	return req;
}
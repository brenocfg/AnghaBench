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
struct nvmefc_fcp_req {struct fcloop_ini_fcpreq* private; } ;
struct nvme_fc_remote_port {struct fcloop_rport* private; } ;
struct nvme_fc_local_port {int dummy; } ;
struct fcloop_rport {TYPE_1__* targetport; } ;
struct fcloop_ini_fcpreq {int /*<<< orphan*/  inilock; struct fcloop_fcpreq* tfcp_req; struct nvmefc_fcp_req* fcpreq; } ;
struct fcloop_fcpreq {int /*<<< orphan*/  fcp_rcv_work; int /*<<< orphan*/  ref; int /*<<< orphan*/  tio_done_work; int /*<<< orphan*/  abort_rcv_work; int /*<<< orphan*/  reqlock; int /*<<< orphan*/  inistate; int /*<<< orphan*/  tport; struct nvmefc_fcp_req* fcpreq; } ;
struct TYPE_2__ {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INI_IO_START ; 
 int /*<<< orphan*/  fcloop_fcp_abort_recv_work ; 
 int /*<<< orphan*/  fcloop_fcp_recv_work ; 
 int /*<<< orphan*/  fcloop_tgt_fcprqst_done_work ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct fcloop_fcpreq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fcloop_fcp_req(struct nvme_fc_local_port *localport,
			struct nvme_fc_remote_port *remoteport,
			void *hw_queue_handle,
			struct nvmefc_fcp_req *fcpreq)
{
	struct fcloop_rport *rport = remoteport->private;
	struct fcloop_ini_fcpreq *inireq = fcpreq->private;
	struct fcloop_fcpreq *tfcp_req;

	if (!rport->targetport)
		return -ECONNREFUSED;

	tfcp_req = kzalloc(sizeof(*tfcp_req), GFP_ATOMIC);
	if (!tfcp_req)
		return -ENOMEM;

	inireq->fcpreq = fcpreq;
	inireq->tfcp_req = tfcp_req;
	spin_lock_init(&inireq->inilock);

	tfcp_req->fcpreq = fcpreq;
	tfcp_req->tport = rport->targetport->private;
	tfcp_req->inistate = INI_IO_START;
	spin_lock_init(&tfcp_req->reqlock);
	INIT_WORK(&tfcp_req->fcp_rcv_work, fcloop_fcp_recv_work);
	INIT_WORK(&tfcp_req->abort_rcv_work, fcloop_fcp_abort_recv_work);
	INIT_WORK(&tfcp_req->tio_done_work, fcloop_tgt_fcprqst_done_work);
	kref_init(&tfcp_req->ref);

	schedule_work(&tfcp_req->fcp_rcv_work);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvmefc_fcp_req {struct fcloop_ini_fcpreq* private; } ;
struct nvme_fc_remote_port {int dummy; } ;
struct nvme_fc_local_port {int dummy; } ;
struct fcloop_ini_fcpreq {int /*<<< orphan*/  inilock; struct fcloop_fcpreq* tfcp_req; } ;
struct fcloop_fcpreq {int inistate; int /*<<< orphan*/  abort_rcv_work; int /*<<< orphan*/  reqlock; } ;

/* Variables and functions */
 int INI_IO_ABORTED ; 
#define  INI_IO_ACTIVE 130 
#define  INI_IO_COMPLETED 129 
#define  INI_IO_START 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fcloop_tfcp_req_get (struct fcloop_fcpreq*) ; 
 int /*<<< orphan*/  fcloop_tfcp_req_put (struct fcloop_fcpreq*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fcloop_fcp_abort(struct nvme_fc_local_port *localport,
			struct nvme_fc_remote_port *remoteport,
			void *hw_queue_handle,
			struct nvmefc_fcp_req *fcpreq)
{
	struct fcloop_ini_fcpreq *inireq = fcpreq->private;
	struct fcloop_fcpreq *tfcp_req;
	bool abortio = true;

	spin_lock(&inireq->inilock);
	tfcp_req = inireq->tfcp_req;
	if (tfcp_req)
		fcloop_tfcp_req_get(tfcp_req);
	spin_unlock(&inireq->inilock);

	if (!tfcp_req)
		/* abort has already been called */
		return;

	/* break initiator/target relationship for io */
	spin_lock_irq(&tfcp_req->reqlock);
	switch (tfcp_req->inistate) {
	case INI_IO_START:
	case INI_IO_ACTIVE:
		tfcp_req->inistate = INI_IO_ABORTED;
		break;
	case INI_IO_COMPLETED:
		abortio = false;
		break;
	default:
		spin_unlock_irq(&tfcp_req->reqlock);
		WARN_ON(1);
		return;
	}
	spin_unlock_irq(&tfcp_req->reqlock);

	if (abortio)
		/* leave the reference while the work item is scheduled */
		WARN_ON(!schedule_work(&tfcp_req->abort_rcv_work));
	else  {
		/*
		 * as the io has already had the done callback made,
		 * nothing more to do. So release the reference taken above
		 */
		fcloop_tfcp_req_put(tfcp_req);
	}
}
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
struct nvme_fc_remote_port {struct lpfc_nvme_rport* private; } ;
struct lpfc_vport {TYPE_1__* phba; } ;
struct lpfc_nvme_rport {struct lpfc_nodelist* ndlp; } ;
struct lpfc_nodelist {int upcall_flags; int /*<<< orphan*/ * nrport; struct lpfc_vport* vport; } ;
struct TYPE_2__ {int /*<<< orphan*/  hbalock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_DISC ; 
 int NLP_WAIT_FOR_UNREG ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct nvme_fc_remote_port*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_nvme_remoteport_delete(struct nvme_fc_remote_port *remoteport)
{
	struct lpfc_nvme_rport *rport = remoteport->private;
	struct lpfc_vport *vport;
	struct lpfc_nodelist *ndlp;

	ndlp = rport->ndlp;
	if (!ndlp)
		goto rport_err;

	vport = ndlp->vport;
	if (!vport)
		goto rport_err;

	/* Remove this rport from the lport's list - memory is owned by the
	 * transport. Remove the ndlp reference for the NVME transport before
	 * calling state machine to remove the node.
	 */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_DISC,
			"6146 remoteport delete of remoteport x%px\n",
			remoteport);
	spin_lock_irq(&vport->phba->hbalock);

	/* The register rebind might have occurred before the delete
	 * downcall.  Guard against this race.
	 */
	if (ndlp->upcall_flags & NLP_WAIT_FOR_UNREG) {
		ndlp->nrport = NULL;
		ndlp->upcall_flags &= ~NLP_WAIT_FOR_UNREG;
	}
	spin_unlock_irq(&vport->phba->hbalock);

	/* Remove original register reference. The host transport
	 * won't reference this rport/remoteport any further.
	 */
	lpfc_nlp_put(ndlp);

 rport_err:
	return;
}
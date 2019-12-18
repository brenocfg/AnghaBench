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
struct TYPE_2__ {struct pci_dev* pdev; int /*<<< orphan*/  host_no; } ;
struct qedi_ctx {int /*<<< orphan*/  max_sqes; int /*<<< orphan*/  max_active_conns; TYPE_1__ dbg_ctx; struct pci_dev* pdev; struct Scsi_Host* shost; } ;
struct pci_dev {int dummy; } ;
struct Scsi_Host {int max_cmd_len; int /*<<< orphan*/  nr_hw_queues; int /*<<< orphan*/  host_no; int /*<<< orphan*/  transportt; int /*<<< orphan*/  max_lun; scalar_t__ max_channel; int /*<<< orphan*/  max_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_MAX_SESS_PER_HBA ; 
 int /*<<< orphan*/  MIN_NUM_CPUS_MSIX (struct qedi_ctx*) ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDI_MAX_ISCSI_CONNS_PER_HBA ; 
 int /*<<< orphan*/  QEDI_SQ_SIZE ; 
 struct Scsi_Host* iscsi_host_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct qedi_ctx* iscsi_host_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  memset (struct qedi_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct qedi_ctx*) ; 
 int /*<<< orphan*/  qedi_host_template ; 
 int /*<<< orphan*/  qedi_scsi_transport ; 

__attribute__((used)) static struct qedi_ctx *qedi_host_alloc(struct pci_dev *pdev)
{
	struct Scsi_Host *shost;
	struct qedi_ctx *qedi = NULL;

	shost = iscsi_host_alloc(&qedi_host_template,
				 sizeof(struct qedi_ctx), 0);
	if (!shost) {
		QEDI_ERR(NULL, "Could not allocate shost\n");
		goto exit_setup_shost;
	}

	shost->max_id = QEDI_MAX_ISCSI_CONNS_PER_HBA;
	shost->max_channel = 0;
	shost->max_lun = ~0;
	shost->max_cmd_len = 16;
	shost->transportt = qedi_scsi_transport;

	qedi = iscsi_host_priv(shost);
	memset(qedi, 0, sizeof(*qedi));
	qedi->shost = shost;
	qedi->dbg_ctx.host_no = shost->host_no;
	qedi->pdev = pdev;
	qedi->dbg_ctx.pdev = pdev;
	qedi->max_active_conns = ISCSI_MAX_SESS_PER_HBA;
	qedi->max_sqes = QEDI_SQ_SIZE;

	shost->nr_hw_queues = MIN_NUM_CPUS_MSIX(qedi);

	pci_set_drvdata(pdev, qedi);

exit_setup_shost:
	return qedi;
}
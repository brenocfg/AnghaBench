#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rsp_que {struct qla_msix_entry* msix; } ;
struct qla_msix_entry {int vector; int entry; int have_irq; int in_use; int /*<<< orphan*/  name; struct rsp_que* handle; } ;
struct TYPE_9__ {int msix_enabled; } ;
struct qla_hw_data {int msix_count; int max_req_queues; int max_rsp_queues; int mqenable; int /*<<< orphan*/  pdev; int /*<<< orphan*/  mqiobase; scalar_t__ msixbase; struct qla_msix_entry* msix_entries; TYPE_1__ flags; scalar_t__ max_qpairs; } ;
struct irq_affinity {int pre_vectors; } ;
struct TYPE_10__ {int irq_offset; int /*<<< orphan*/  host_no; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_12__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ATIO_MSIX_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_P3P_TYPE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA83XX (struct qla_hw_data*) ; 
 int PCI_IRQ_AFFINITY ; 
 int PCI_IRQ_MSIX ; 
 size_t QLA_ATIO_VECTOR ; 
 int QLA_BASE_VECTORS ; 
 scalar_t__ QLA_TGT_MODE_ENABLED () ; 
 scalar_t__ USER_CTRL_IRQ (struct qla_hw_data*) ; 
 struct qla_msix_entry* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 TYPE_8__* msix_entries ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int,int,int) ; 
 int pci_alloc_irq_vectors_affinity (int /*<<< orphan*/ ,int,int,int,struct irq_affinity*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 TYPE_2__* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ql2xenablemsix ; 
 scalar_t__ ql2xmqsupport ; 
 scalar_t__ ql2xnvmeenable ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_dbg_multiq ; 
 int /*<<< orphan*/  ql_dbg_pci (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  qla2x00_free_irqs (TYPE_2__*) ; 
 TYPE_3__* qla82xx_msix_entries ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rsp_que*) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla24xx_enable_msix(struct qla_hw_data *ha, struct rsp_que *rsp)
{
	int i, ret;
	struct qla_msix_entry *qentry;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	int min_vecs = QLA_BASE_VECTORS;
	struct irq_affinity desc = {
		.pre_vectors = QLA_BASE_VECTORS,
	};

	if (QLA_TGT_MODE_ENABLED() && (ql2xenablemsix != 0) &&
	    IS_ATIO_MSIX_CAPABLE(ha)) {
		desc.pre_vectors++;
		min_vecs++;
	}

	if (USER_CTRL_IRQ(ha) || !ha->mqiobase) {
		/* user wants to control IRQ setting for target mode */
		ret = pci_alloc_irq_vectors(ha->pdev, min_vecs,
		    ha->msix_count, PCI_IRQ_MSIX);
	} else
		ret = pci_alloc_irq_vectors_affinity(ha->pdev, min_vecs,
		    ha->msix_count, PCI_IRQ_MSIX | PCI_IRQ_AFFINITY,
		    &desc);

	if (ret < 0) {
		ql_log(ql_log_fatal, vha, 0x00c7,
		    "MSI-X: Failed to enable support, "
		    "giving   up -- %d/%d.\n",
		    ha->msix_count, ret);
		goto msix_out;
	} else if (ret < ha->msix_count) {
		ql_log(ql_log_info, vha, 0x00c6,
		    "MSI-X: Using %d vectors\n", ret);
		ha->msix_count = ret;
		/* Recalculate queue values */
		if (ha->mqiobase && (ql2xmqsupport || ql2xnvmeenable)) {
			ha->max_req_queues = ha->msix_count - 1;

			/* ATIOQ needs 1 vector. That's 1 less QPair */
			if (QLA_TGT_MODE_ENABLED())
				ha->max_req_queues--;

			ha->max_rsp_queues = ha->max_req_queues;

			ha->max_qpairs = ha->max_req_queues - 1;
			ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0190,
			    "Adjusted Max no of queues pairs: %d.\n", ha->max_qpairs);
		}
	}
	vha->irq_offset = desc.pre_vectors;
	ha->msix_entries = kcalloc(ha->msix_count,
				   sizeof(struct qla_msix_entry),
				   GFP_KERNEL);
	if (!ha->msix_entries) {
		ql_log(ql_log_fatal, vha, 0x00c8,
		    "Failed to allocate memory for ha->msix_entries.\n");
		ret = -ENOMEM;
		goto free_irqs;
	}
	ha->flags.msix_enabled = 1;

	for (i = 0; i < ha->msix_count; i++) {
		qentry = &ha->msix_entries[i];
		qentry->vector = pci_irq_vector(ha->pdev, i);
		qentry->entry = i;
		qentry->have_irq = 0;
		qentry->in_use = 0;
		qentry->handle = NULL;
	}

	/* Enable MSI-X vectors for the base queue */
	for (i = 0; i < QLA_BASE_VECTORS; i++) {
		qentry = &ha->msix_entries[i];
		qentry->handle = rsp;
		rsp->msix = qentry;
		scnprintf(qentry->name, sizeof(qentry->name),
		    "qla2xxx%lu_%s", vha->host_no, msix_entries[i].name);
		if (IS_P3P_TYPE(ha))
			ret = request_irq(qentry->vector,
				qla82xx_msix_entries[i].handler,
				0, qla82xx_msix_entries[i].name, rsp);
		else
			ret = request_irq(qentry->vector,
				msix_entries[i].handler,
				0, qentry->name, rsp);
		if (ret)
			goto msix_register_fail;
		qentry->have_irq = 1;
		qentry->in_use = 1;
	}

	/*
	 * If target mode is enable, also request the vector for the ATIO
	 * queue.
	 */
	if (QLA_TGT_MODE_ENABLED() && (ql2xenablemsix != 0) &&
	    IS_ATIO_MSIX_CAPABLE(ha)) {
		qentry = &ha->msix_entries[QLA_ATIO_VECTOR];
		rsp->msix = qentry;
		qentry->handle = rsp;
		scnprintf(qentry->name, sizeof(qentry->name),
		    "qla2xxx%lu_%s", vha->host_no,
		    msix_entries[QLA_ATIO_VECTOR].name);
		qentry->in_use = 1;
		ret = request_irq(qentry->vector,
			msix_entries[QLA_ATIO_VECTOR].handler,
			0, qentry->name, rsp);
		qentry->have_irq = 1;
	}

msix_register_fail:
	if (ret) {
		ql_log(ql_log_fatal, vha, 0x00cb,
		    "MSI-X: unable to register handler -- %x/%d.\n",
		    qentry->vector, ret);
		qla2x00_free_irqs(vha);
		ha->mqenable = 0;
		goto msix_out;
	}

	/* Enable MSI-X vector for response queue update for queue 0 */
	if (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) {
		if (ha->msixbase && ha->mqiobase &&
		    (ha->max_rsp_queues > 1 || ha->max_req_queues > 1 ||
		     ql2xmqsupport))
			ha->mqenable = 1;
	} else
		if (ha->mqiobase &&
		    (ha->max_rsp_queues > 1 || ha->max_req_queues > 1 ||
		     ql2xmqsupport))
			ha->mqenable = 1;
	ql_dbg(ql_dbg_multiq, vha, 0xc005,
	    "mqiobase=%p, max_rsp_queues=%d, max_req_queues=%d.\n",
	    ha->mqiobase, ha->max_rsp_queues, ha->max_req_queues);
	ql_dbg(ql_dbg_init, vha, 0x0055,
	    "mqiobase=%p, max_rsp_queues=%d, max_req_queues=%d.\n",
	    ha->mqiobase, ha->max_rsp_queues, ha->max_req_queues);

msix_out:
	return ret;

free_irqs:
	pci_free_irq_vectors(ha->pdev);
	goto msix_out;
}
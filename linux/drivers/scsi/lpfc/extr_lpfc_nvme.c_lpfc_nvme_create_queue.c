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
typedef  int /*<<< orphan*/  u16 ;
struct nvme_fc_local_port {scalar_t__ private; } ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nvme_qhandle {unsigned int qidx; unsigned int index; int /*<<< orphan*/  cpu_id; } ;
struct lpfc_nvme_lport {struct lpfc_vport* vport; } ;
struct TYPE_2__ {unsigned int max_hw_queues; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME ; 
 struct lpfc_nvme_qhandle* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ lpfc_nvme_template ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,unsigned int,int /*<<< orphan*/ ,unsigned int,struct lpfc_nvme_qhandle*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

__attribute__((used)) static int
lpfc_nvme_create_queue(struct nvme_fc_local_port *pnvme_lport,
		       unsigned int qidx, u16 qsize,
		       void **handle)
{
	struct lpfc_nvme_lport *lport;
	struct lpfc_vport *vport;
	struct lpfc_nvme_qhandle *qhandle;
	char *str;

	if (!pnvme_lport->private)
		return -ENOMEM;

	lport = (struct lpfc_nvme_lport *)pnvme_lport->private;
	vport = lport->vport;
	qhandle = kzalloc(sizeof(struct lpfc_nvme_qhandle), GFP_KERNEL);
	if (qhandle == NULL)
		return -ENOMEM;

	qhandle->cpu_id = raw_smp_processor_id();
	qhandle->qidx = qidx;
	/*
	 * NVME qidx == 0 is the admin queue, so both admin queue
	 * and first IO queue will use MSI-X vector and associated
	 * EQ/CQ/WQ at index 0. After that they are sequentially assigned.
	 */
	if (qidx) {
		str = "IO ";  /* IO queue */
		qhandle->index = ((qidx - 1) %
			lpfc_nvme_template.max_hw_queues);
	} else {
		str = "ADM";  /* Admin queue */
		qhandle->index = qidx;
	}

	lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME,
			 "6073 Binding %s HdwQueue %d  (cpu %d) to "
			 "hdw_queue %d qhandle x%px\n", str,
			 qidx, qhandle->cpu_id, qhandle->index, qhandle);
	*handle = (void *)qhandle;
	return 0;
}
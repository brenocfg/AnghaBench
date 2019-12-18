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
struct nvme_fc_local_port {scalar_t__ private; } ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nvme_lport {struct lpfc_vport* vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct lpfc_nvme_lport*,unsigned int,void*) ; 

__attribute__((used)) static void
lpfc_nvme_delete_queue(struct nvme_fc_local_port *pnvme_lport,
		       unsigned int qidx,
		       void *handle)
{
	struct lpfc_nvme_lport *lport;
	struct lpfc_vport *vport;

	if (!pnvme_lport->private)
		return;

	lport = (struct lpfc_nvme_lport *)pnvme_lport->private;
	vport = lport->vport;

	lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME,
			"6001 ENTER.  lpfc_pnvme x%px, qidx x%x qhandle x%px\n",
			lport, qidx, handle);
	kfree(handle);
}
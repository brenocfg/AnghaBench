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
struct nvme_fc_local_port {struct lpfc_nvme_lport* private; } ;
struct lpfc_nvme_lport {int /*<<< orphan*/  lport_unreg_cmp; TYPE_1__* vport; } ;
struct TYPE_2__ {scalar_t__ localport; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct lpfc_nvme_lport*) ; 

__attribute__((used)) static void
lpfc_nvme_localport_delete(struct nvme_fc_local_port *localport)
{
	struct lpfc_nvme_lport *lport = localport->private;

	lpfc_printf_vlog(lport->vport, KERN_INFO, LOG_NVME,
			 "6173 localport x%px delete complete\n",
			 lport);

	/* release any threads waiting for the unreg to complete */
	if (lport->vport->localport)
		complete(lport->lport_unreg_cmp);
}
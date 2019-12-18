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
struct ctlr_info {struct Scsi_Host* scsi_host; TYPE_1__* pdev; int /*<<< orphan*/  maxsgentries; scalar_t__ nr_cmds; } ;
struct Scsi_Host {int this_id; int max_channel; unsigned long* hostdata; int /*<<< orphan*/  irq; int /*<<< orphan*/  unique_id; int /*<<< orphan*/  transportt; int /*<<< orphan*/  sg_tablesize; scalar_t__ can_queue; scalar_t__ cmd_per_lun; void* max_id; void* max_lun; int /*<<< orphan*/  max_cmd_len; scalar_t__ n_io_port; scalar_t__ io_port; } ;
typedef  int /*<<< orphan*/  h ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* HPSA_MAX_LUN ; 
 scalar_t__ HPSA_NRESERVED_CMDS ; 
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hpsa_driver_template ; 
 int /*<<< orphan*/  hpsa_sas_transport_template ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hpsa_scsi_host_alloc(struct ctlr_info *h)
{
	struct Scsi_Host *sh;

	sh = scsi_host_alloc(&hpsa_driver_template, sizeof(h));
	if (sh == NULL) {
		dev_err(&h->pdev->dev, "scsi_host_alloc failed\n");
		return -ENOMEM;
	}

	sh->io_port = 0;
	sh->n_io_port = 0;
	sh->this_id = -1;
	sh->max_channel = 3;
	sh->max_cmd_len = MAX_COMMAND_SIZE;
	sh->max_lun = HPSA_MAX_LUN;
	sh->max_id = HPSA_MAX_LUN;
	sh->can_queue = h->nr_cmds - HPSA_NRESERVED_CMDS;
	sh->cmd_per_lun = sh->can_queue;
	sh->sg_tablesize = h->maxsgentries;
	sh->transportt = hpsa_sas_transport_template;
	sh->hostdata[0] = (unsigned long) h;
	sh->irq = pci_irq_vector(h->pdev, 0);
	sh->unique_id = sh->irq;

	h->scsi_host = sh;
	return 0;
}
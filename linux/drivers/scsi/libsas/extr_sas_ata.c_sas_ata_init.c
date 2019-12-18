#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct Scsi_Host* shost; } ;
struct sas_ha_struct {int /*<<< orphan*/  dev; TYPE_2__ core; } ;
struct TYPE_6__ {struct ata_port* ap; struct ata_host* ata_host; } ;
struct domain_device {TYPE_3__ sata_dev; TYPE_1__* port; } ;
struct ata_port {struct Scsi_Host* scsi_host; int /*<<< orphan*/  cbl; struct domain_device* private_data; } ;
struct ata_host {int /*<<< orphan*/  dev; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {struct sas_ha_struct* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_SATA ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ata_host_init (struct ata_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_host_put (struct ata_host*) ; 
 struct ata_port* ata_sas_port_alloc (struct ata_host*,int /*<<< orphan*/ *,struct Scsi_Host*) ; 
 int /*<<< orphan*/  ata_sas_port_destroy (struct ata_port*) ; 
 int ata_sas_port_init (struct ata_port*) ; 
 int ata_sas_tport_add (int /*<<< orphan*/ ,struct ata_port*) ; 
 struct ata_host* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sas_sata_ops ; 
 int /*<<< orphan*/  sata_port_info ; 

int sas_ata_init(struct domain_device *found_dev)
{
	struct sas_ha_struct *ha = found_dev->port->ha;
	struct Scsi_Host *shost = ha->core.shost;
	struct ata_host *ata_host;
	struct ata_port *ap;
	int rc;

	ata_host = kzalloc(sizeof(*ata_host), GFP_KERNEL);
	if (!ata_host)	{
		pr_err("ata host alloc failed.\n");
		return -ENOMEM;
	}

	ata_host_init(ata_host, ha->dev, &sas_sata_ops);

	ap = ata_sas_port_alloc(ata_host, &sata_port_info, shost);
	if (!ap) {
		pr_err("ata_sas_port_alloc failed.\n");
		rc = -ENODEV;
		goto free_host;
	}

	ap->private_data = found_dev;
	ap->cbl = ATA_CBL_SATA;
	ap->scsi_host = shost;
	rc = ata_sas_port_init(ap);
	if (rc)
		goto destroy_port;

	rc = ata_sas_tport_add(ata_host->dev, ap);
	if (rc)
		goto destroy_port;

	found_dev->sata_dev.ata_host = ata_host;
	found_dev->sata_dev.ap = ap;

	return 0;

destroy_port:
	ata_sas_port_destroy(ap);
free_host:
	ata_host_put(ata_host);
	return rc;
}
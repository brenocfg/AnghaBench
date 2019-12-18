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
struct scsi_host_template {int this_id; int /*<<< orphan*/  name; } ;
struct qlogicfas408_priv {int qlirq; int qbase; int qinitid; int /*<<< orphan*/  qinfo; int /*<<< orphan*/  int_type; struct Scsi_Host* shost; } ;
struct pcmcia_device {int dummy; } ;
struct Scsi_Host {int io_port; int n_io_port; int dma_channel; int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_TYPE ; 
 int QL_TURBO_PDMA ; 
 int /*<<< orphan*/  free_irq (int,struct Scsi_Host*) ; 
 struct qlogicfas408_priv* get_priv_by_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  qlogic_name ; 
 int qlogicfas408_get_chip_type (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlogicfas408_ihandl ; 
 int /*<<< orphan*/  qlogicfas408_setup (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 scalar_t__ scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 

__attribute__((used)) static struct Scsi_Host *qlogic_detect(struct scsi_host_template *host,
				struct pcmcia_device *link, int qbase, int qlirq)
{
	int qltyp;		/* type of chip */
	int qinitid;
	struct Scsi_Host *shost;	/* registered host structure */
	struct qlogicfas408_priv *priv;

	qltyp = qlogicfas408_get_chip_type(qbase, INT_TYPE);
	qinitid = host->this_id;
	if (qinitid < 0)
		qinitid = 7;	/* if no ID, use 7 */

	qlogicfas408_setup(qbase, qinitid, INT_TYPE);

	host->name = qlogic_name;
	shost = scsi_host_alloc(host, sizeof(struct qlogicfas408_priv));
	if (!shost)
		goto err;
	shost->io_port = qbase;
	shost->n_io_port = 16;
	shost->dma_channel = -1;
	if (qlirq != -1)
		shost->irq = qlirq;

	priv = get_priv_by_host(shost);
	priv->qlirq = qlirq;
	priv->qbase = qbase;
	priv->qinitid = qinitid;
	priv->shost = shost;
	priv->int_type = INT_TYPE;					

	if (request_irq(qlirq, qlogicfas408_ihandl, 0, qlogic_name, shost))
		goto free_scsi_host;

	sprintf(priv->qinfo,
		"Qlogicfas Driver version 0.46, chip %02X at %03X, IRQ %d, TPdma:%d",
		qltyp, qbase, qlirq, QL_TURBO_PDMA);

	if (scsi_add_host(shost, NULL))
		goto free_interrupt;

	scsi_scan_host(shost);

	return shost;

free_interrupt:
	free_irq(qlirq, shost);

free_scsi_host:
	scsi_host_put(shost);
	
err:
	return NULL;
}
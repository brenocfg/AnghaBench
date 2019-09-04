#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_host_template {int dummy; } ;
struct ata_host {int n_ports; TYPE_1__** ports; int /*<<< orphan*/  dev; struct ahci_host_priv* private_data; } ;
struct ahci_port_priv {int /*<<< orphan*/  irq_desc; } ;
struct ahci_host_priv {int (* get_irq_vector ) (struct ata_host*,int) ;} ;
struct TYPE_3__ {struct ahci_port_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahci_multi_irqs_intr_hard ; 
 int ata_host_register (struct ata_host*,struct scsi_host_template*) ; 
 int ata_host_start (struct ata_host*) ; 
 int /*<<< orphan*/  ata_port_desc (TYPE_1__*,char*,int) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int stub1 (struct ata_host*,int) ; 

__attribute__((used)) static int ahci_host_activate_multi_irqs(struct ata_host *host,
					 struct scsi_host_template *sht)
{
	struct ahci_host_priv *hpriv = host->private_data;
	int i, rc;

	rc = ata_host_start(host);
	if (rc)
		return rc;
	/*
	 * Requests IRQs according to AHCI-1.1 when multiple MSIs were
	 * allocated. That is one MSI per port, starting from @irq.
	 */
	for (i = 0; i < host->n_ports; i++) {
		struct ahci_port_priv *pp = host->ports[i]->private_data;
		int irq = hpriv->get_irq_vector(host, i);

		/* Do not receive interrupts sent by dummy ports */
		if (!pp) {
			disable_irq(irq);
			continue;
		}

		rc = devm_request_irq(host->dev, irq, ahci_multi_irqs_intr_hard,
				0, pp->irq_desc, host->ports[i]);

		if (rc)
			return rc;
		ata_port_desc(host->ports[i], "irq %d", irq);
	}

	return ata_host_register(host, sht);
}
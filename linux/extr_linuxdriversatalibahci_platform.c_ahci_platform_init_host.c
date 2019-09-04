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
struct scsi_host_template {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
typedef  struct ata_port_info {int flags; void* private_data; } const ata_port_info ;
struct ata_port {int port_no; int flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  em_message_type; } ;
struct ata_host {int n_ports; struct ata_port** ports; int /*<<< orphan*/  flags; struct ahci_host_priv* private_data; } ;
struct ahci_host_priv {int irq; int cap; int port_map; int /*<<< orphan*/  em_msg_type; scalar_t__ flags; } ;

/* Variables and functions */
 int ATA_FLAG_EM ; 
 int ATA_FLAG_NCQ ; 
 int ATA_FLAG_PMP ; 
 int /*<<< orphan*/  ATA_HOST_PARALLEL_SCAN ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int HOST_CAP_64 ; 
 int HOST_CAP_NCQ ; 
 int HOST_CAP_PMP ; 
 int HOST_CAP_SSS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int ahci_host_activate (struct ata_host*,struct scsi_host_template*) ; 
 scalar_t__ ahci_ignore_sss ; 
 int /*<<< orphan*/  ahci_init_controller (struct ata_host*) ; 
 int /*<<< orphan*/  ahci_nr_ports (int) ; 
 int /*<<< orphan*/  ahci_print_info (struct ata_host*,char*) ; 
 int ahci_reset_controller (struct ata_host*) ; 
 int /*<<< orphan*/  ahci_reset_em (struct ata_host*) ; 
 int /*<<< orphan*/  ahci_save_initial_config (struct device*,struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_set_em_messages (struct ahci_host_priv*,struct ata_port_info const*) ; 
 int /*<<< orphan*/  ata_dummy_port_ops ; 
 struct ata_host* ata_host_alloc_pinfo (struct device*,struct ata_port_info const**,int) ; 
 int /*<<< orphan*/  ata_port_desc (struct ata_port*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fls (int) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ahci_platform_init_host(struct platform_device *pdev,
			    struct ahci_host_priv *hpriv,
			    const struct ata_port_info *pi_template,
			    struct scsi_host_template *sht)
{
	struct device *dev = &pdev->dev;
	struct ata_port_info pi = *pi_template;
	const struct ata_port_info *ppi[] = { &pi, NULL };
	struct ata_host *host;
	int i, irq, n_ports, rc;

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		if (irq != -EPROBE_DEFER)
			dev_err(dev, "no irq\n");
		return irq;
	}

	hpriv->irq = irq;

	/* prepare host */
	pi.private_data = (void *)(unsigned long)hpriv->flags;

	ahci_save_initial_config(dev, hpriv);

	if (hpriv->cap & HOST_CAP_NCQ)
		pi.flags |= ATA_FLAG_NCQ;

	if (hpriv->cap & HOST_CAP_PMP)
		pi.flags |= ATA_FLAG_PMP;

	ahci_set_em_messages(hpriv, &pi);

	/* CAP.NP sometimes indicate the index of the last enabled
	 * port, at other times, that of the last possible port, so
	 * determining the maximum port number requires looking at
	 * both CAP.NP and port_map.
	 */
	n_ports = max(ahci_nr_ports(hpriv->cap), fls(hpriv->port_map));

	host = ata_host_alloc_pinfo(dev, ppi, n_ports);
	if (!host)
		return -ENOMEM;

	host->private_data = hpriv;

	if (!(hpriv->cap & HOST_CAP_SSS) || ahci_ignore_sss)
		host->flags |= ATA_HOST_PARALLEL_SCAN;
	else
		dev_info(dev, "SSS flag set, parallel bus scan disabled\n");

	if (pi.flags & ATA_FLAG_EM)
		ahci_reset_em(host);

	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];

		ata_port_desc(ap, "mmio %pR",
			      platform_get_resource(pdev, IORESOURCE_MEM, 0));
		ata_port_desc(ap, "port 0x%x", 0x100 + ap->port_no * 0x80);

		/* set enclosure management message type */
		if (ap->flags & ATA_FLAG_EM)
			ap->em_message_type = hpriv->em_msg_type;

		/* disabled/not-implemented port */
		if (!(hpriv->port_map & (1 << i)))
			ap->ops = &ata_dummy_port_ops;
	}

	if (hpriv->cap & HOST_CAP_64) {
		rc = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(64));
		if (rc) {
			rc = dma_coerce_mask_and_coherent(dev,
							  DMA_BIT_MASK(32));
			if (rc) {
				dev_err(dev, "Failed to enable 64-bit DMA.\n");
				return rc;
			}
			dev_warn(dev, "Enable 32-bit DMA instead of 64-bit.\n");
		}
	}

	rc = ahci_reset_controller(host);
	if (rc)
		return rc;

	ahci_init_controller(host);
	ahci_print_info(host, "platform");

	return ahci_host_activate(host, sht);
}
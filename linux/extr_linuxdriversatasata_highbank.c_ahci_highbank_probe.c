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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ecx_plat_data {int /*<<< orphan*/  n_ports; } ;
typedef  struct ata_port_info {int /*<<< orphan*/  flags; scalar_t__ private_data; } const ata_port_info ;
struct ata_port {int port_no; int flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  em_message_type; } ;
struct ata_host {int n_ports; struct ata_port** ports; int /*<<< orphan*/  flags; struct ahci_host_priv* private_data; } ;
struct ahci_host_priv {int irq; unsigned long flags; int cap; int port_map; int /*<<< orphan*/  em_msg_type; struct ecx_plat_data* plat_data; int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
 int ATA_FLAG_EM ; 
 int /*<<< orphan*/  ATA_FLAG_NCQ ; 
 int /*<<< orphan*/  ATA_FLAG_PMP ; 
 int /*<<< orphan*/  ATA_HOST_PARALLEL_SCAN ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HOST_CAP_64 ; 
 int HOST_CAP_NCQ ; 
 int HOST_CAP_PMP ; 
 int HOST_CAP_SSS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  ahci_highbank_platform_sht ; 
 struct ata_port_info const ahci_highbank_port_info ; 
 int ahci_host_activate (struct ata_host*,int /*<<< orphan*/ *) ; 
 scalar_t__ ahci_ignore_sss ; 
 int /*<<< orphan*/  ahci_init_controller (struct ata_host*) ; 
 int /*<<< orphan*/  ahci_nr_ports (int) ; 
 int /*<<< orphan*/  ahci_print_info (struct ata_host*,char*) ; 
 int ahci_reset_controller (struct ata_host*) ; 
 int /*<<< orphan*/  ahci_save_initial_config (struct device*,struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ata_dummy_port_ops ; 
 struct ata_host* ata_host_alloc_pinfo (struct device*,struct ata_port_info const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_port_desc (struct ata_port*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fls (int) ; 
 int highbank_initialize_phys (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  highbank_set_em_messages (struct device*,struct ahci_host_priv*,struct ata_port_info const*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int ahci_highbank_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ahci_host_priv *hpriv;
	struct ecx_plat_data *pdata;
	struct ata_host *host;
	struct resource *mem;
	int irq;
	int i;
	int rc;
	u32 n_ports;
	struct ata_port_info pi = ahci_highbank_port_info;
	const struct ata_port_info *ppi[] = { &pi, NULL };

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!mem) {
		dev_err(dev, "no mmio space\n");
		return -EINVAL;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		dev_err(dev, "no irq\n");
		return -EINVAL;
	}

	hpriv = devm_kzalloc(dev, sizeof(*hpriv), GFP_KERNEL);
	if (!hpriv) {
		dev_err(dev, "can't alloc ahci_host_priv\n");
		return -ENOMEM;
	}
	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		dev_err(dev, "can't alloc ecx_plat_data\n");
		return -ENOMEM;
	}

	hpriv->irq = irq;
	hpriv->flags |= (unsigned long)pi.private_data;

	hpriv->mmio = devm_ioremap(dev, mem->start, resource_size(mem));
	if (!hpriv->mmio) {
		dev_err(dev, "can't map %pR\n", mem);
		return -ENOMEM;
	}

	rc = highbank_initialize_phys(dev, hpriv->mmio);
	if (rc)
		return rc;


	ahci_save_initial_config(dev, hpriv);

	/* prepare host */
	if (hpriv->cap & HOST_CAP_NCQ)
		pi.flags |= ATA_FLAG_NCQ;

	if (hpriv->cap & HOST_CAP_PMP)
		pi.flags |= ATA_FLAG_PMP;

	if (hpriv->cap & HOST_CAP_64)
		dma_set_coherent_mask(dev, DMA_BIT_MASK(64));

	/* CAP.NP sometimes indicate the index of the last enabled
	 * port, at other times, that of the last possible port, so
	 * determining the maximum port number requires looking at
	 * both CAP.NP and port_map.
	 */
	n_ports = max(ahci_nr_ports(hpriv->cap), fls(hpriv->port_map));

	pdata->n_ports = n_ports;
	hpriv->plat_data = pdata;
	highbank_set_em_messages(dev, hpriv, &pi);

	host = ata_host_alloc_pinfo(dev, ppi, n_ports);
	if (!host) {
		rc = -ENOMEM;
		goto err0;
	}

	host->private_data = hpriv;

	if (!(hpriv->cap & HOST_CAP_SSS) || ahci_ignore_sss)
		host->flags |= ATA_HOST_PARALLEL_SCAN;

	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];

		ata_port_desc(ap, "mmio %pR", mem);
		ata_port_desc(ap, "port 0x%x", 0x100 + ap->port_no * 0x80);

		/* set enclosure management message type */
		if (ap->flags & ATA_FLAG_EM)
			ap->em_message_type = hpriv->em_msg_type;

		/* disabled/not-implemented port */
		if (!(hpriv->port_map & (1 << i)))
			ap->ops = &ata_dummy_port_ops;
	}

	rc = ahci_reset_controller(host);
	if (rc)
		goto err0;

	ahci_init_controller(host);
	ahci_print_info(host, "platform");

	rc = ahci_host_activate(host, &ahci_highbank_platform_sht);
	if (rc)
		goto err0;

	return 0;
err0:
	return rc;
}
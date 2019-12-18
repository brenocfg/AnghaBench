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
struct qm_portal_config {int cpu; int irq; int /*<<< orphan*/  addr_virt_ce; int /*<<< orphan*/  addr_virt_ci; int /*<<< orphan*/  pools; int /*<<< orphan*/  channel; struct device* dev; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DPAA_PORTAL_CE ; 
 int /*<<< orphan*/  DPAA_PORTAL_CI ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  QBMAN_MEMREMAP_ATTR ; 
 int __qman_portals_probed ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int cpumask_next_zero (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct qm_portal_config* devm_kmalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_set_mask (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_pcfg (struct qm_portal_config*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memunmap (int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portal_cpus ; 
 int qm_get_fqid_maxcnt () ; 
 int /*<<< orphan*/  qm_get_pools_sdqcr () ; 
 int /*<<< orphan*/  qman_done_cleanup () ; 
 int qman_is_probed () ; 
 int /*<<< orphan*/  qman_lock ; 
 int /*<<< orphan*/  qman_offline_cpu (int) ; 
 scalar_t__ qman_requires_cleanup () ; 
 int qman_shutdown_fq (int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qman_portal_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct qm_portal_config *pcfg;
	struct resource *addr_phys[2];
	int irq, cpu, err, i;
	u32 val;

	err = qman_is_probed();
	if (!err)
		return -EPROBE_DEFER;
	if (err < 0) {
		dev_err(&pdev->dev, "failing probe due to qman probe error\n");
		return -ENODEV;
	}

	pcfg = devm_kmalloc(dev, sizeof(*pcfg), GFP_KERNEL);
	if (!pcfg) {
		__qman_portals_probed = -1;
		return -ENOMEM;
	}

	pcfg->dev = dev;

	addr_phys[0] = platform_get_resource(pdev, IORESOURCE_MEM,
					     DPAA_PORTAL_CE);
	if (!addr_phys[0]) {
		dev_err(dev, "Can't get %pOF property 'reg::CE'\n", node);
		goto err_ioremap1;
	}

	addr_phys[1] = platform_get_resource(pdev, IORESOURCE_MEM,
					     DPAA_PORTAL_CI);
	if (!addr_phys[1]) {
		dev_err(dev, "Can't get %pOF property 'reg::CI'\n", node);
		goto err_ioremap1;
	}

	err = of_property_read_u32(node, "cell-index", &val);
	if (err) {
		dev_err(dev, "Can't get %pOF property 'cell-index'\n", node);
		__qman_portals_probed = -1;
		return err;
	}
	pcfg->channel = val;
	pcfg->cpu = -1;
	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		goto err_ioremap1;
	pcfg->irq = irq;

	pcfg->addr_virt_ce = memremap(addr_phys[0]->start,
					resource_size(addr_phys[0]),
					QBMAN_MEMREMAP_ATTR);
	if (!pcfg->addr_virt_ce) {
		dev_err(dev, "memremap::CE failed\n");
		goto err_ioremap1;
	}

	pcfg->addr_virt_ci = ioremap(addr_phys[1]->start,
				resource_size(addr_phys[1]));
	if (!pcfg->addr_virt_ci) {
		dev_err(dev, "ioremap::CI failed\n");
		goto err_ioremap2;
	}

	pcfg->pools = qm_get_pools_sdqcr();

	spin_lock(&qman_lock);
	cpu = cpumask_next_zero(-1, &portal_cpus);
	if (cpu >= nr_cpu_ids) {
		__qman_portals_probed = 1;
		/* unassigned portal, skip init */
		spin_unlock(&qman_lock);
		return 0;
	}

	cpumask_set_cpu(cpu, &portal_cpus);
	spin_unlock(&qman_lock);
	pcfg->cpu = cpu;

	if (dma_set_mask(dev, DMA_BIT_MASK(40))) {
		dev_err(dev, "dma_set_mask() failed\n");
		goto err_portal_init;
	}

	if (!init_pcfg(pcfg)) {
		dev_err(dev, "portal init failed\n");
		goto err_portal_init;
	}

	/* clear irq affinity if assigned cpu is offline */
	if (!cpu_online(cpu))
		qman_offline_cpu(cpu);

	if (__qman_portals_probed == 1 && qman_requires_cleanup()) {
		/*
		 * QMan wasn't reset prior to boot (Kexec for example)
		 * Empty all the frame queues so they are in reset state
		 */
		for (i = 0; i < qm_get_fqid_maxcnt(); i++) {
			err =  qman_shutdown_fq(i);
			if (err) {
				dev_err(dev, "Failed to shutdown frame queue %d\n",
					i);
				goto err_portal_init;
			}
		}
		qman_done_cleanup();
	}

	return 0;

err_portal_init:
	iounmap(pcfg->addr_virt_ci);
err_ioremap2:
	memunmap(pcfg->addr_virt_ce);
err_ioremap1:
	__qman_portals_probed = -1;

	return -ENXIO;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ngene {TYPE_2__* pci_dev; TYPE_1__* channel; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  i2c_switch_mutex; int /*<<< orphan*/  pll_mutex; int /*<<< orphan*/  stream_mutex; int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  rx_wq; int /*<<< orphan*/  tx_wq; int /*<<< orphan*/  cmd_wq; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int MAX_STREAM ; 
 int /*<<< orphan*/  NGENE_INT_ENABLE ; 
 int /*<<< orphan*/  TIMESTAMPS ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ngene*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_handler ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ngene_i2c_init (struct ngene*,int) ; 
 int /*<<< orphan*/  ngene_init (struct ngene*) ; 
 int ngene_load_firm (struct ngene*) ; 
 int /*<<< orphan*/  ngwritel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_2__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ngene_start(struct ngene *dev)
{
	int stat;
	int i;

	pci_set_master(dev->pci_dev);
	ngene_init(dev);

	stat = request_irq(dev->pci_dev->irq, irq_handler,
			   IRQF_SHARED, "nGene",
			   (void *)dev);
	if (stat < 0)
		return stat;

	init_waitqueue_head(&dev->cmd_wq);
	init_waitqueue_head(&dev->tx_wq);
	init_waitqueue_head(&dev->rx_wq);
	mutex_init(&dev->cmd_mutex);
	mutex_init(&dev->stream_mutex);
	sema_init(&dev->pll_mutex, 1);
	mutex_init(&dev->i2c_switch_mutex);
	spin_lock_init(&dev->cmd_lock);
	for (i = 0; i < MAX_STREAM; i++)
		spin_lock_init(&dev->channel[i].state_lock);
	ngwritel(1, TIMESTAMPS);

	ngwritel(1, NGENE_INT_ENABLE);

	stat = ngene_load_firm(dev);
	if (stat < 0)
		goto fail;

#ifdef CONFIG_PCI_MSI
	/* enable MSI if kernel and card support it */
	if (pci_msi_enabled() && dev->card_info->msi_supported) {
		struct device *pdev = &dev->pci_dev->dev;
		unsigned long flags;

		ngwritel(0, NGENE_INT_ENABLE);
		free_irq(dev->pci_dev->irq, dev);
		stat = pci_enable_msi(dev->pci_dev);
		if (stat) {
			dev_info(pdev, "MSI not available\n");
			flags = IRQF_SHARED;
		} else {
			flags = 0;
			dev->msi_enabled = true;
		}
		stat = request_irq(dev->pci_dev->irq, irq_handler,
					flags, "nGene", dev);
		if (stat < 0)
			goto fail2;
		ngwritel(1, NGENE_INT_ENABLE);
	}
#endif

	stat = ngene_i2c_init(dev, 0);
	if (stat < 0)
		goto fail;

	stat = ngene_i2c_init(dev, 1);
	if (stat < 0)
		goto fail;

	return 0;

fail:
	ngwritel(0, NGENE_INT_ENABLE);
	free_irq(dev->pci_dev->irq, dev);
#ifdef CONFIG_PCI_MSI
fail2:
	if (dev->msi_enabled)
		pci_disable_msi(dev->pci_dev);
#endif
	return stat;
}
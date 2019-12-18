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
struct ngene {TYPE_2__* pci_dev; scalar_t__ msi_enabled; TYPE_1__* channel; int /*<<< orphan*/  cmd_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGENE_COMMAND ; 
 int /*<<< orphan*/  NGENE_COMMAND_HI ; 
 int /*<<< orphan*/  NGENE_EVENT ; 
 int /*<<< orphan*/  NGENE_EVENT_HI ; 
 int /*<<< orphan*/  NGENE_INT_ENABLE ; 
 int /*<<< orphan*/  NGENE_STATUS ; 
 int /*<<< orphan*/  NGENE_STATUS_HI ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ngene*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngwritel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_2__*) ; 

__attribute__((used)) static void ngene_stop(struct ngene *dev)
{
	mutex_destroy(&dev->cmd_mutex);
	i2c_del_adapter(&(dev->channel[0].i2c_adapter));
	i2c_del_adapter(&(dev->channel[1].i2c_adapter));
	ngwritel(0, NGENE_INT_ENABLE);
	ngwritel(0, NGENE_COMMAND);
	ngwritel(0, NGENE_COMMAND_HI);
	ngwritel(0, NGENE_STATUS);
	ngwritel(0, NGENE_STATUS_HI);
	ngwritel(0, NGENE_EVENT);
	ngwritel(0, NGENE_EVENT_HI);
	free_irq(dev->pci_dev->irq, dev);
#ifdef CONFIG_PCI_MSI
	if (dev->msi_enabled)
		pci_disable_msi(dev->pci_dev);
#endif
}
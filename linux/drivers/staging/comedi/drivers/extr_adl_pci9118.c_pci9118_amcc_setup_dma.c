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
struct pci9118_private {scalar_t__ iobase_a; struct pci9118_dmabuf* dmabuf; } ;
struct pci9118_dmabuf {int /*<<< orphan*/  use_size; int /*<<< orphan*/  hw; } ;
struct comedi_device {struct pci9118_private* private; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_MWAR ; 
 scalar_t__ AMCC_OP_REG_MWTC ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pci9118_amcc_setup_dma(struct comedi_device *dev, unsigned int buf)
{
	struct pci9118_private *devpriv = dev->private;
	struct pci9118_dmabuf *dmabuf = &devpriv->dmabuf[buf];

	/* set the master write address and transfer count */
	outl(dmabuf->hw, devpriv->iobase_a + AMCC_OP_REG_MWAR);
	outl(dmabuf->use_size, devpriv->iobase_a + AMCC_OP_REG_MWTC);
}
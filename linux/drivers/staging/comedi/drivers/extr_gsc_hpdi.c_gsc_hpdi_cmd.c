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
typedef  int u32 ;
struct hpdi_private {int dma_desc_phys_addr; int dio_count; scalar_t__ plx9080_mmio; scalar_t__ dma_desc_index; } ;
struct comedi_subdevice {scalar_t__ io_bits; struct comedi_async* async; } ;
struct comedi_device {scalar_t__ mmio; int /*<<< orphan*/  spinlock; struct hpdi_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; int stop_arg; } ;
struct comedi_async {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ BOARD_CONTROL_REG ; 
 scalar_t__ BOARD_STATUS_REG ; 
 int EINVAL ; 
 scalar_t__ INTERRUPT_CONTROL_REG ; 
 int PLX_DMACSR_CLEARINTR ; 
 int PLX_DMACSR_ENABLE ; 
 int PLX_DMACSR_START ; 
 int PLX_DMADPR_DESCPCI ; 
 int PLX_DMADPR_TCINTR ; 
 int PLX_DMADPR_XFERL2P ; 
 scalar_t__ PLX_REG_DMACSR0 ; 
 scalar_t__ PLX_REG_DMADPR0 ; 
 scalar_t__ PLX_REG_DMALADR0 ; 
 scalar_t__ PLX_REG_DMAPADR0 ; 
 scalar_t__ PLX_REG_DMASIZ0 ; 
 int RX_ENABLE_BIT ; 
 int RX_FIFO_RESET_BIT ; 
 int RX_FULL_INTR ; 
 int RX_OVERRUN_BIT ; 
 int RX_UNDERRUN_BIT ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  gsc_hpdi_abort_dma (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int gsc_hpdi_cmd(struct comedi_device *dev,
			struct comedi_subdevice *s)
{
	struct hpdi_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned long flags;
	u32 bits;

	if (s->io_bits)
		return -EINVAL;

	writel(RX_FIFO_RESET_BIT, dev->mmio + BOARD_CONTROL_REG);

	gsc_hpdi_abort_dma(dev, 0);

	devpriv->dma_desc_index = 0;

	/*
	 * These register are supposedly unused during chained dma,
	 * but I have found that left over values from last operation
	 * occasionally cause problems with transfer of first dma
	 * block.  Initializing them to zero seems to fix the problem.
	 */
	writel(0, devpriv->plx9080_mmio + PLX_REG_DMASIZ0);
	writel(0, devpriv->plx9080_mmio + PLX_REG_DMAPADR0);
	writel(0, devpriv->plx9080_mmio + PLX_REG_DMALADR0);

	/* give location of first dma descriptor */
	bits = devpriv->dma_desc_phys_addr | PLX_DMADPR_DESCPCI |
	       PLX_DMADPR_TCINTR | PLX_DMADPR_XFERL2P;
	writel(bits, devpriv->plx9080_mmio + PLX_REG_DMADPR0);

	/* enable dma transfer */
	spin_lock_irqsave(&dev->spinlock, flags);
	writeb(PLX_DMACSR_ENABLE | PLX_DMACSR_START | PLX_DMACSR_CLEARINTR,
	       devpriv->plx9080_mmio + PLX_REG_DMACSR0);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	if (cmd->stop_src == TRIG_COUNT)
		devpriv->dio_count = cmd->stop_arg;
	else
		devpriv->dio_count = 1;

	/* clear over/under run status flags */
	writel(RX_UNDERRUN_BIT | RX_OVERRUN_BIT, dev->mmio + BOARD_STATUS_REG);

	/* enable interrupts */
	writel(RX_FULL_INTR, dev->mmio + INTERRUPT_CONTROL_REG);

	writel(RX_ENABLE_BIT, dev->mmio + BOARD_CONTROL_REG);

	return 0;
}
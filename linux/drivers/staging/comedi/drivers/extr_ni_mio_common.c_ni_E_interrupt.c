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
struct ni_private {scalar_t__ is_m_series; int /*<<< orphan*/  mite_channel_lock; scalar_t__ ao_mite_chan; scalar_t__ ai_mite_chan; scalar_t__ mite; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  attached; struct ni_private* private; struct comedi_subdevice* write_subdev; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned short NISTC_AI_STATUS1_INTA ; 
 int /*<<< orphan*/  NISTC_AI_STATUS1_REG ; 
 unsigned short NISTC_AO_STATUS1_INTB ; 
 int /*<<< orphan*/  NISTC_AO_STATUS1_REG ; 
 int /*<<< orphan*/  ack_a_interrupt (struct comedi_device*,unsigned short) ; 
 int /*<<< orphan*/  ack_b_interrupt (struct comedi_device*,unsigned short) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  handle_a_interrupt (struct comedi_device*,struct comedi_subdevice*,unsigned short) ; 
 int /*<<< orphan*/  handle_b_interrupt (struct comedi_device*,struct comedi_subdevice*,unsigned short) ; 
 int /*<<< orphan*/  handle_cdio_interrupt (struct comedi_device*) ; 
 int /*<<< orphan*/  handle_gpct_interrupt (struct comedi_device*,int) ; 
 int /*<<< orphan*/  mite_ack_linkc (scalar_t__,struct comedi_subdevice*,int) ; 
 unsigned short ni_stc_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t ni_E_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s_ai = dev->read_subdev;
	struct comedi_subdevice *s_ao = dev->write_subdev;
	unsigned short a_status;
	unsigned short b_status;
	unsigned long flags;
#ifdef PCIDMA
	struct ni_private *devpriv = dev->private;
#endif

	if (!dev->attached)
		return IRQ_NONE;
	smp_mb();		/* make sure dev->attached is checked */

	/*  lock to avoid race with comedi_poll */
	spin_lock_irqsave(&dev->spinlock, flags);
	a_status = ni_stc_readw(dev, NISTC_AI_STATUS1_REG);
	b_status = ni_stc_readw(dev, NISTC_AO_STATUS1_REG);
#ifdef PCIDMA
	if (devpriv->mite) {
		unsigned long flags_too;

		spin_lock_irqsave(&devpriv->mite_channel_lock, flags_too);
		if (s_ai && devpriv->ai_mite_chan)
			mite_ack_linkc(devpriv->ai_mite_chan, s_ai, false);
		if (s_ao && devpriv->ao_mite_chan)
			mite_ack_linkc(devpriv->ao_mite_chan, s_ao, false);
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags_too);
	}
#endif
	ack_a_interrupt(dev, a_status);
	ack_b_interrupt(dev, b_status);
	if (s_ai) {
		if (a_status & NISTC_AI_STATUS1_INTA)
			handle_a_interrupt(dev, s_ai, a_status);
		/* handle any interrupt or dma events */
		comedi_handle_events(dev, s_ai);
	}
	if (s_ao) {
		if (b_status & NISTC_AO_STATUS1_INTB)
			handle_b_interrupt(dev, s_ao, b_status);
		/* handle any interrupt or dma events */
		comedi_handle_events(dev, s_ao);
	}
	handle_gpct_interrupt(dev, 0);
	handle_gpct_interrupt(dev, 1);
#ifdef PCIDMA
	if (devpriv->is_m_series)
		handle_cdio_interrupt(dev);
#endif

	spin_unlock_irqrestore(&dev->spinlock, flags);
	return IRQ_HANDLED;
}
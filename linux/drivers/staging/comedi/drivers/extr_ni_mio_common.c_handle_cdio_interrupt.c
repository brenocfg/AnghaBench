#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ni_private {int /*<<< orphan*/  mite_channel_lock; scalar_t__ cdo_mite_chan; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct comedi_subdevice* subdevices; struct ni_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 size_t NI_DIO_SUBDEV ; 
 int /*<<< orphan*/  NI_M_CDIO_CMD_REG ; 
 unsigned int NI_M_CDIO_STATUS_CDO_ERROR ; 
 unsigned int NI_M_CDIO_STATUS_CDO_FIFO_EMPTY ; 
 int /*<<< orphan*/  NI_M_CDIO_STATUS_REG ; 
 int /*<<< orphan*/  NI_M_CDO_CMD_ERR_INT_CONFIRM ; 
 int /*<<< orphan*/  NI_M_CDO_CMD_F_E_INT_ENA_CLR ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  mite_ack_linkc (scalar_t__,struct comedi_subdevice*,int) ; 
 unsigned int ni_readl (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void handle_cdio_interrupt(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	unsigned int cdio_status;
	struct comedi_subdevice *s = &dev->subdevices[NI_DIO_SUBDEV];
	unsigned long flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->cdo_mite_chan)
		mite_ack_linkc(devpriv->cdo_mite_chan, s, true);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	cdio_status = ni_readl(dev, NI_M_CDIO_STATUS_REG);
	if (cdio_status & NI_M_CDIO_STATUS_CDO_ERROR) {
		/* XXX just guessing this is needed and does something useful */
		ni_writel(dev, NI_M_CDO_CMD_ERR_INT_CONFIRM,
			  NI_M_CDIO_CMD_REG);
		s->async->events |= COMEDI_CB_OVERFLOW;
	}
	if (cdio_status & NI_M_CDIO_STATUS_CDO_FIFO_EMPTY) {
		ni_writel(dev, NI_M_CDO_CMD_F_E_INT_ENA_CLR,
			  NI_M_CDIO_CMD_REG);
		/* s->async->events |= COMEDI_CB_EOA; */
	}
	comedi_handle_events(dev, s);
}
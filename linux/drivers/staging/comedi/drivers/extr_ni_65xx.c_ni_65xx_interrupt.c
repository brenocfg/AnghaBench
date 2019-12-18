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
struct comedi_subdevice {int /*<<< orphan*/  state; } ;
struct comedi_device {scalar_t__ mmio; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int NI_65XX_CLR_EDGE_INT ; 
 int NI_65XX_CLR_OVERFLOW_INT ; 
 scalar_t__ NI_65XX_CLR_REG ; 
 unsigned int NI_65XX_STATUS_EDGE_INT ; 
 unsigned int NI_65XX_STATUS_INT ; 
 scalar_t__ NI_65XX_STATUS_REG ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t ni_65xx_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int status;

	status = readb(dev->mmio + NI_65XX_STATUS_REG);
	if ((status & NI_65XX_STATUS_INT) == 0)
		return IRQ_NONE;
	if ((status & NI_65XX_STATUS_EDGE_INT) == 0)
		return IRQ_NONE;

	writeb(NI_65XX_CLR_EDGE_INT | NI_65XX_CLR_OVERFLOW_INT,
	       dev->mmio + NI_65XX_CLR_REG);

	comedi_buf_write_samples(s, &s->state, 1);
	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}
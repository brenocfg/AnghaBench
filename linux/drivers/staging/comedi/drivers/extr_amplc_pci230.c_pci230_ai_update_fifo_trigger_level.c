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
struct pci230_private {scalar_t__ hwver; unsigned int adcfifothresh; unsigned short adccon; scalar_t__ daqio; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct pci230_private* private; } ;
struct comedi_cmd {int flags; unsigned int scan_end_arg; } ;
struct TYPE_2__ {unsigned int cur_chan; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CMDF_WAKE_EOS ; 
 scalar_t__ PCI230P_ADCFFTH ; 
 unsigned short PCI230P_ADC_INT_FIFO_THRESH ; 
 scalar_t__ PCI230_ADCCON ; 
 unsigned int PCI230_ADC_FIFOLEVEL_HALFFULL ; 
 unsigned short PCI230_ADC_INT_FIFO_HALF ; 
 unsigned short PCI230_ADC_INT_FIFO_MASK ; 
 unsigned short PCI230_ADC_INT_FIFO_NEMPTY ; 
 unsigned int comedi_nsamples_left (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static void pci230_ai_update_fifo_trigger_level(struct comedi_device *dev,
						struct comedi_subdevice *s)
{
	struct pci230_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int wake;
	unsigned short triglev;
	unsigned short adccon;

	if (cmd->flags & CMDF_WAKE_EOS)
		wake = cmd->scan_end_arg - s->async->cur_chan;
	else
		wake = comedi_nsamples_left(s, PCI230_ADC_FIFOLEVEL_HALFFULL);

	if (wake >= PCI230_ADC_FIFOLEVEL_HALFFULL) {
		triglev = PCI230_ADC_INT_FIFO_HALF;
	} else if (wake > 1 && devpriv->hwver > 0) {
		/* PCI230+/260+ programmable FIFO interrupt level. */
		if (devpriv->adcfifothresh != wake) {
			devpriv->adcfifothresh = wake;
			outw(wake, devpriv->daqio + PCI230P_ADCFFTH);
		}
		triglev = PCI230P_ADC_INT_FIFO_THRESH;
	} else {
		triglev = PCI230_ADC_INT_FIFO_NEMPTY;
	}
	adccon = (devpriv->adccon & ~PCI230_ADC_INT_FIFO_MASK) | triglev;
	if (adccon != devpriv->adccon) {
		devpriv->adccon = adccon;
		outw(adccon, devpriv->daqio + PCI230_ADCCON);
	}
}
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
struct pcidas64_private {scalar_t__ main_iobase; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ mmio; struct comedi_subdevice* read_subdev; struct pcidas64_private* private; } ;

/* Variables and functions */
 scalar_t__ ADC_FIFO_REG ; 
 scalar_t__ ADC_READ_PNTR_REG ; 
 scalar_t__ ADC_WRITE_PNTR_REG ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 unsigned int comedi_nsamples_left (struct comedi_subdevice*,int) ; 
 int readl (scalar_t__) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static void pio_drain_ai_fifo_32(struct comedi_device *dev)
{
	struct pcidas64_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int nsamples;
	unsigned int i;
	u32 fifo_data;
	int write_code =
		readw(devpriv->main_iobase + ADC_WRITE_PNTR_REG) & 0x7fff;
	int read_code =
		readw(devpriv->main_iobase + ADC_READ_PNTR_REG) & 0x7fff;

	nsamples = comedi_nsamples_left(s, 100000);
	for (i = 0; read_code != write_code && i < nsamples;) {
		unsigned short val;

		fifo_data = readl(dev->mmio + ADC_FIFO_REG);
		val = fifo_data & 0xffff;
		comedi_buf_write_samples(s, &val, 1);
		i++;
		if (i < nsamples) {
			val = (fifo_data >> 16) & 0xffff;
			comedi_buf_write_samples(s, &val, 1);
			i++;
		}
		read_code = readw(devpriv->main_iobase + ADC_READ_PNTR_REG) &
			    0x7fff;
	}
}
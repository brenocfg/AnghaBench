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
struct labpc_private {unsigned int (* read_byte ) (struct comedi_device*,int /*<<< orphan*/ ) ;} ;
struct comedi_device {struct labpc_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_FIFO_REG ; 
 unsigned int stub1 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int labpc_read_adc_fifo(struct comedi_device *dev)
{
	struct labpc_private *devpriv = dev->private;
	unsigned int lsb = devpriv->read_byte(dev, ADC_FIFO_REG);
	unsigned int msb = devpriv->read_byte(dev, ADC_FIFO_REG);

	return (msb << 8) | lsb;
}
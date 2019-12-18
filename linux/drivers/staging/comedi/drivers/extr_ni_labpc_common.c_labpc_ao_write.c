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
struct labpc_private {int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ;} ;
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_device {struct labpc_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_LSB_REG (unsigned int) ; 
 int /*<<< orphan*/  DAC_MSB_REG (unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void labpc_ao_write(struct comedi_device *dev,
			   struct comedi_subdevice *s,
			   unsigned int chan, unsigned int val)
{
	struct labpc_private *devpriv = dev->private;

	devpriv->write_byte(dev, val & 0xff, DAC_LSB_REG(chan));
	devpriv->write_byte(dev, (val >> 8) & 0xff, DAC_MSB_REG(chan));

	s->readback[chan] = val;
}
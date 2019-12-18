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
struct pcl812_private {int mode_reg_int; TYPE_1__* dma; scalar_t__ ai_dma; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  pacer; scalar_t__ iobase; struct pcl812_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int PCL812_CTRL_DISABLE_TRIG ; 
 scalar_t__ PCL812_CTRL_REG ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_isadma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  pcl812_ai_clear_eoc (struct comedi_device*) ; 

__attribute__((used)) static int pcl812_ai_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct pcl812_private *devpriv = dev->private;

	if (devpriv->ai_dma)
		comedi_isadma_disable(devpriv->dma->chan);

	outb(devpriv->mode_reg_int | PCL812_CTRL_DISABLE_TRIG,
	     dev->iobase + PCL812_CTRL_REG);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);
	pcl812_ai_clear_eoc(dev);
	return 0;
}
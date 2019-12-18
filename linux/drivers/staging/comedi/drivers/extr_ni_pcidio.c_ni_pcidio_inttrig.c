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
struct nidio96_private {int /*<<< orphan*/  OP_MODEBits; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ mmio; struct nidio96_private* private; } ;
struct comedi_cmd {unsigned int start_arg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OP_MODE ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ni_pcidio_inttrig(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     unsigned int trig_num)
{
	struct nidio96_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;

	if (trig_num != cmd->start_arg)
		return -EINVAL;

	writeb(devpriv->OP_MODEBits, dev->mmio + OP_MODE);
	s->async->inttrig = NULL;

	return 1;
}
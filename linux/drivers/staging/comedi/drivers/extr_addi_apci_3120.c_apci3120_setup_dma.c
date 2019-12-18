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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct apci3120_private* private; } ;
struct comedi_cmd {int scan_end_arg; scalar_t__ stop_src; unsigned int stop_arg; int flags; } ;
struct apci3120_private {struct apci3120_dmabuf* dmabuf; } ;
struct apci3120_dmabuf {unsigned int size; unsigned int use_size; } ;
struct TYPE_2__ {unsigned int prealloc_bufsz; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CMDF_WAKE_EOS ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  apci3120_init_dma (struct comedi_device*,struct apci3120_dmabuf*) ; 
 unsigned int comedi_samples_to_bytes (struct comedi_subdevice*,int) ; 

__attribute__((used)) static void apci3120_setup_dma(struct comedi_device *dev,
			       struct comedi_subdevice *s)
{
	struct apci3120_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	struct apci3120_dmabuf *dmabuf0 = &devpriv->dmabuf[0];
	struct apci3120_dmabuf *dmabuf1 = &devpriv->dmabuf[1];
	unsigned int dmalen0 = dmabuf0->size;
	unsigned int dmalen1 = dmabuf1->size;
	unsigned int scan_bytes;

	scan_bytes = comedi_samples_to_bytes(s, cmd->scan_end_arg);

	if (cmd->stop_src == TRIG_COUNT) {
		/*
		 * Must we fill full first buffer? And must we fill
		 * full second buffer when first is once filled?
		 */
		if (dmalen0 > (cmd->stop_arg * scan_bytes))
			dmalen0 = cmd->stop_arg * scan_bytes;
		else if (dmalen1 > (cmd->stop_arg * scan_bytes - dmalen0))
			dmalen1 = cmd->stop_arg * scan_bytes - dmalen0;
	}

	if (cmd->flags & CMDF_WAKE_EOS) {
		/* don't we want wake up every scan? */
		if (dmalen0 > scan_bytes) {
			dmalen0 = scan_bytes;
			if (cmd->scan_end_arg & 1)
				dmalen0 += 2;
		}
		if (dmalen1 > scan_bytes) {
			dmalen1 = scan_bytes;
			if (cmd->scan_end_arg & 1)
				dmalen1 -= 2;
			if (dmalen1 < 4)
				dmalen1 = 4;
		}
	} else {
		/* isn't output buff smaller that our DMA buff? */
		if (dmalen0 > s->async->prealloc_bufsz)
			dmalen0 = s->async->prealloc_bufsz;
		if (dmalen1 > s->async->prealloc_bufsz)
			dmalen1 = s->async->prealloc_bufsz;
	}
	dmabuf0->use_size = dmalen0;
	dmabuf1->use_size = dmalen1;

	apci3120_init_dma(dev, dmabuf0);
}
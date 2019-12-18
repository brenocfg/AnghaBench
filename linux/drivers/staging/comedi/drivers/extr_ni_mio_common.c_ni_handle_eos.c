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
struct ni_private {scalar_t__ aimode; int ai_cmd2; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct ni_private* private; } ;
struct TYPE_2__ {int events; } ;

/* Variables and functions */
 scalar_t__ AIMODE_SCAN ; 
 int COMEDI_CB_EOS ; 
 int NISTC_AI_CMD2_END_ON_EOS ; 
 int /*<<< orphan*/  ni_handle_fifo_dregs (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_sync_ai_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  shutdown_ai_command (struct comedi_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ni_handle_eos(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct ni_private *devpriv = dev->private;

	if (devpriv->aimode == AIMODE_SCAN) {
#ifdef PCIDMA
		static const int timeout = 10;
		int i;

		for (i = 0; i < timeout; i++) {
			ni_sync_ai_dma(dev);
			if ((s->async->events & COMEDI_CB_EOS))
				break;
			udelay(1);
		}
#else
		ni_handle_fifo_dregs(dev);
		s->async->events |= COMEDI_CB_EOS;
#endif
	}
	/* handle special case of single scan */
	if (devpriv->ai_cmd2 & NISTC_AI_CMD2_END_ON_EOS)
		shutdown_ai_command(dev);
}
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
struct pcidas64_private {scalar_t__ ai_cmd_running; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct pcidas64_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort_dma (struct comedi_device*,int) ; 
 int /*<<< orphan*/  disable_ai_pacing (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ai_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pcidas64_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	if (devpriv->ai_cmd_running == 0) {
		spin_unlock_irqrestore(&dev->spinlock, flags);
		return 0;
	}
	devpriv->ai_cmd_running = 0;
	spin_unlock_irqrestore(&dev->spinlock, flags);

	disable_ai_pacing(dev);

	abort_dma(dev, 1);

	return 0;
}
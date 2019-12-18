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
struct ni_private {int /*<<< orphan*/  window_lock; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI611X_AO_WINDOW_ADDR_REG ; 
 int /*<<< orphan*/  NI611X_AO_WINDOW_DATA_REG ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writew (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void ni_ao_win_outl(struct comedi_device *dev,
				  unsigned int data, int addr)
{
	struct ni_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&devpriv->window_lock, flags);
	ni_writew(dev, addr, NI611X_AO_WINDOW_ADDR_REG);
	ni_writel(dev, data, NI611X_AO_WINDOW_DATA_REG);
	spin_unlock_irqrestore(&devpriv->window_lock, flags);
}
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
struct comedi_subdevice {struct apci2032_int_private* private; } ;
struct comedi_device {int dummy; } ;
struct apci2032_int_private {int /*<<< orphan*/  spinlock; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  apci2032_int_stop (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int apci2032_int_cancel(struct comedi_device *dev,
			       struct comedi_subdevice *s)
{
	struct apci2032_int_private *subpriv = s->private;
	unsigned long flags;

	spin_lock_irqsave(&subpriv->spinlock, flags);
	if (subpriv->active)
		apci2032_int_stop(dev, s);
	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	return 0;
}
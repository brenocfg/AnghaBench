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
struct vnt_private {int /*<<< orphan*/  lock; TYPE_1__* usb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vnt_start_interrupt_urb (struct vnt_private*) ; 

int vnt_int_start_interrupt(struct vnt_private *priv)
{
	int ret = 0;
	unsigned long flags;

	dev_dbg(&priv->usb->dev, "---->Interrupt Polling Thread\n");

	spin_lock_irqsave(&priv->lock, flags);

	ret = vnt_start_interrupt_urb(priv);

	spin_unlock_irqrestore(&priv->lock, flags);

	return ret;
}
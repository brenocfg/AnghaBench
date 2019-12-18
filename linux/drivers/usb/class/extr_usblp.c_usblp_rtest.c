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
struct usblp {int /*<<< orphan*/  lock; scalar_t__ rcomplete; int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int ENODEV ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int usblp_rtest(struct usblp *usblp, int nonblock)
{
	unsigned long flags;

	if (!usblp->present)
		return -ENODEV;
	if (signal_pending(current))
		return -EINTR;
	spin_lock_irqsave(&usblp->lock, flags);
	if (usblp->rcomplete) {
		spin_unlock_irqrestore(&usblp->lock, flags);
		return 0;
	}
	spin_unlock_irqrestore(&usblp->lock, flags);
	if (nonblock)
		return -EAGAIN;
	return 1;
}
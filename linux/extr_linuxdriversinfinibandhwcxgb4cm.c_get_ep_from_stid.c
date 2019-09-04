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
struct c4iw_listen_ep {int /*<<< orphan*/  com; } ;
struct c4iw_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  stid_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_get_ep (int /*<<< orphan*/ *) ; 
 struct c4iw_listen_ep* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct c4iw_listen_ep *get_ep_from_stid(struct c4iw_dev *dev,
					       unsigned int stid)
{
	struct c4iw_listen_ep *ep;
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);
	ep = idr_find(&dev->stid_idr, stid);
	if (ep)
		c4iw_get_ep(&ep->com);
	spin_unlock_irqrestore(&dev->lock, flags);
	return ep;
}
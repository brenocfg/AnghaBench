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
struct ican3_msg {int dummy; } ;
struct ican3_dev {scalar_t__ iftype; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ican3_new_recv_msg (struct ican3_dev*,struct ican3_msg*) ; 
 int ican3_old_recv_msg (struct ican3_dev*,struct ican3_msg*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ican3_recv_msg(struct ican3_dev *mod, struct ican3_msg *msg)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&mod->lock, flags);

	if (mod->iftype == 0)
		ret = ican3_old_recv_msg(mod, msg);
	else
		ret = ican3_new_recv_msg(mod, msg);

	spin_unlock_irqrestore(&mod->lock, flags);
	return ret;
}
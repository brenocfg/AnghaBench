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
struct seq_file {struct mtu3* private; } ;
struct mtu3_ep {int flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct mtu3 {int num_eps; int /*<<< orphan*/  lock; struct mtu3_ep* out_eps; struct mtu3_ep* in_eps; } ;

/* Variables and functions */
 int MTU3_EP_ENABLED ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mtu3_ep_used_show(struct seq_file *sf, void *unused)
{
	struct mtu3 *mtu = sf->private;
	struct mtu3_ep *mep;
	unsigned long flags;
	int used = 0;
	int i;

	spin_lock_irqsave(&mtu->lock, flags);

	for (i = 0; i < mtu->num_eps; i++) {
		mep = mtu->in_eps + i;
		if (mep->flags & MTU3_EP_ENABLED) {
			seq_printf(sf, "%s - type: %d\n", mep->name, mep->type);
			used++;
		}

		mep = mtu->out_eps + i;
		if (mep->flags & MTU3_EP_ENABLED) {
			seq_printf(sf, "%s - type: %d\n", mep->name, mep->type);
			used++;
		}
	}
	seq_printf(sf, "total used: %d eps\n", used);

	spin_unlock_irqrestore(&mtu->lock, flags);

	return 0;
}
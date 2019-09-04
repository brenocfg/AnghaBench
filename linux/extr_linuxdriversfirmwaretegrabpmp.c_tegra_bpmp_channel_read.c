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
struct tegra_bpmp_channel {struct tegra_bpmp* bpmp; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  allocated; } ;
struct tegra_bpmp {TYPE_1__ threaded; int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int __tegra_bpmp_channel_read (struct tegra_bpmp_channel*,void*,size_t,int*) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tegra_bpmp_channel_get_thread_index (struct tegra_bpmp_channel*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t tegra_bpmp_channel_read(struct tegra_bpmp_channel *channel,
				       void *data, size_t size, int *ret)
{
	struct tegra_bpmp *bpmp = channel->bpmp;
	unsigned long flags;
	ssize_t err;
	int index;

	index = tegra_bpmp_channel_get_thread_index(channel);
	if (index < 0) {
		err = index;
		goto unlock;
	}

	spin_lock_irqsave(&bpmp->lock, flags);
	err = __tegra_bpmp_channel_read(channel, data, size, ret);
	clear_bit(index, bpmp->threaded.allocated);
	spin_unlock_irqrestore(&bpmp->lock, flags);

unlock:
	up(&bpmp->threaded.lock);

	return err;
}
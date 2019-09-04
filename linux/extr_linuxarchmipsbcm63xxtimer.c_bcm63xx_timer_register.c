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
struct TYPE_2__ {void (* cb ) (void*) ;void* data; } ;

/* Variables and functions */
 int BCM63XX_TIMER_COUNT ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* timer_data ; 
 int /*<<< orphan*/  timer_data_lock ; 

int bcm63xx_timer_register(int id, void (*callback)(void *data), void *data)
{
	unsigned long flags;
	int ret;

	if (id >= BCM63XX_TIMER_COUNT || !callback)
		return -EINVAL;

	ret = 0;
	raw_spin_lock_irqsave(&timer_data_lock, flags);
	if (timer_data[id].cb) {
		ret = -EBUSY;
		goto out;
	}

	timer_data[id].cb = callback;
	timer_data[id].data = data;

out:
	raw_spin_unlock_irqrestore(&timer_data_lock, flags);
	return ret;
}
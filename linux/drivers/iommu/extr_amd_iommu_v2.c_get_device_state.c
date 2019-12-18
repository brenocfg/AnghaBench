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
typedef  int /*<<< orphan*/  u16 ;
struct device_state {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 struct device_state* __get_device_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  state_lock ; 

__attribute__((used)) static struct device_state *get_device_state(u16 devid)
{
	struct device_state *dev_state;
	unsigned long flags;

	spin_lock_irqsave(&state_lock, flags);
	dev_state = __get_device_state(devid);
	if (dev_state != NULL)
		atomic_inc(&dev_state->count);
	spin_unlock_irqrestore(&state_lock, flags);

	return dev_state;
}
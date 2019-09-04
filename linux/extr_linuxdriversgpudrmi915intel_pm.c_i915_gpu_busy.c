#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int awake; } ;
struct TYPE_4__ {TYPE_1__ gt; } ;

/* Variables and functions */
 TYPE_2__* i915_mch_dev ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

bool i915_gpu_busy(void)
{
	bool ret = false;

	spin_lock_irq(&mchdev_lock);
	if (i915_mch_dev)
		ret = i915_mch_dev->gt.awake;
	spin_unlock_irq(&mchdev_lock);

	return ret;
}
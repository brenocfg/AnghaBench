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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (struct timer_list*) ; 
 int /*<<< orphan*/  mce_device_remove (unsigned int) ; 
 int /*<<< orphan*/  mce_disable_cpu () ; 
 int /*<<< orphan*/  mce_threshold_remove_device (unsigned int) ; 
 int /*<<< orphan*/  mce_timer ; 
 struct timer_list* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mce_cpu_pre_down(unsigned int cpu)
{
	struct timer_list *t = this_cpu_ptr(&mce_timer);

	mce_disable_cpu();
	del_timer_sync(t);
	mce_threshold_remove_device(cpu);
	mce_device_remove(cpu);
	return 0;
}
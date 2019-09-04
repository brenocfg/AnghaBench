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
struct timespec64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msr_kvm_wall_clock ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  pvclock_read_wallclock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timespec64*) ; 
 int /*<<< orphan*/  slow_virt_to_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_pvti () ; 
 int /*<<< orphan*/  wall_clock ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_get_wallclock(struct timespec64 *now)
{
	wrmsrl(msr_kvm_wall_clock, slow_virt_to_phys(&wall_clock));
	preempt_disable();
	pvclock_read_wallclock(&wall_clock, this_cpu_pvti(), now);
	preempt_enable();
}
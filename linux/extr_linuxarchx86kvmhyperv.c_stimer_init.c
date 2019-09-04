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
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct kvm_vcpu_hv_stimer {int index; TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kvm_vcpu_hv_stimer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stimer_prepare_msg (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  stimer_timer_callback ; 

__attribute__((used)) static void stimer_init(struct kvm_vcpu_hv_stimer *stimer, int timer_index)
{
	memset(stimer, 0, sizeof(*stimer));
	stimer->index = timer_index;
	hrtimer_init(&stimer->timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	stimer->timer.function = stimer_timer_callback;
	stimer_prepare_msg(stimer);
}
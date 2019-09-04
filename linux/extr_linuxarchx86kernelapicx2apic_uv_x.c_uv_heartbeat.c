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
struct timer_list {int dummy; } ;
struct TYPE_2__ {unsigned char state; } ;

/* Variables and functions */
 unsigned char SCIR_CPU_ACTIVITY ; 
 scalar_t__ SCIR_CPU_HB_INTERVAL ; 
 unsigned char SCIR_CPU_HEARTBEAT ; 
 scalar_t__ idle_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,scalar_t__) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 TYPE_1__* uv_scir_info ; 
 int /*<<< orphan*/  uv_set_scir_bits (unsigned char) ; 

__attribute__((used)) static void uv_heartbeat(struct timer_list *timer)
{
	unsigned char bits = uv_scir_info->state;

	/* Flip heartbeat bit: */
	bits ^= SCIR_CPU_HEARTBEAT;

	/* Is this CPU idle? */
	if (idle_cpu(raw_smp_processor_id()))
		bits &= ~SCIR_CPU_ACTIVITY;
	else
		bits |= SCIR_CPU_ACTIVITY;

	/* Update system controller interface reg: */
	uv_set_scir_bits(bits);

	/* Enable next timer period: */
	mod_timer(timer, jiffies + SCIR_CPU_HB_INTERVAL);
}
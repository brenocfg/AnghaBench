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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCR_ENAMODE_ONESHOT_MASK ; 
 int keystone_timer_config (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keystone_set_next_event(unsigned long cycles,
				  struct clock_event_device *evt)
{
	return keystone_timer_config(cycles, TCR_ENAMODE_ONESHOT_MASK);
}
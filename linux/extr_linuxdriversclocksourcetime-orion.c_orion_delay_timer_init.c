#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long freq; } ;

/* Variables and functions */
 TYPE_1__ orion_delay_timer ; 
 int /*<<< orphan*/  register_current_timer_delay (TYPE_1__*) ; 

__attribute__((used)) static void orion_delay_timer_init(unsigned long rate)
{
	orion_delay_timer.freq = rate;
	register_current_timer_delay(&orion_delay_timer);
}
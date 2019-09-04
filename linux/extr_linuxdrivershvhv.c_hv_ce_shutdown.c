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
 scalar_t__ direct_mode_enabled ; 
 int /*<<< orphan*/  hv_disable_stimer0_percpu_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_init_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_init_timer_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stimer0_irq ; 

__attribute__((used)) static int hv_ce_shutdown(struct clock_event_device *evt)
{
	hv_init_timer(0, 0);
	hv_init_timer_config(0, 0);
	if (direct_mode_enabled)
		hv_disable_stimer0_percpu_irq(stimer0_irq);

	return 0;
}
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
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hz_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCR_ENAMODE_PERIODIC_MASK ; 
 int /*<<< orphan*/  keystone_timer_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ timer ; 

__attribute__((used)) static int keystone_set_periodic(struct clock_event_device *evt)
{
	keystone_timer_config(timer.hz_period, TCR_ENAMODE_PERIODIC_MASK);
	return 0;
}
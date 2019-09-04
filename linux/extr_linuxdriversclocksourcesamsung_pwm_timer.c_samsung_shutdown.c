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
struct TYPE_2__ {int /*<<< orphan*/  event_id; } ;

/* Variables and functions */
 TYPE_1__ pwm ; 
 int /*<<< orphan*/  samsung_time_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int samsung_shutdown(struct clock_event_device *evt)
{
	samsung_time_stop(pwm.event_id);
	return 0;
}
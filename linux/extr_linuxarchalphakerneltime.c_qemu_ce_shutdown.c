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
 int /*<<< orphan*/  qemu_set_alarm_abs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qemu_ce_shutdown(struct clock_event_device *ce)
{
	/* The mode member of CE is updated for us in generic code.
	   Just make sure that the event is disabled.  */
	qemu_set_alarm_abs(0);
	return 0;
}
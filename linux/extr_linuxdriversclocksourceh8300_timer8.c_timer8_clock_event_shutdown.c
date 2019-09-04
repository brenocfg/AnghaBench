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
 int /*<<< orphan*/  ced_to_priv (struct clock_event_device*) ; 
 int /*<<< orphan*/  timer8_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int timer8_clock_event_shutdown(struct clock_event_device *ced)
{
	timer8_stop(ced_to_priv(ced));
	return 0;
}
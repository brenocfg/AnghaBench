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
struct TYPE_2__ {scalar_t__ clock_comparator; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 scalar_t__ get_tod_clock () ; 
 int /*<<< orphan*/  set_clock_comparator (scalar_t__) ; 

__attribute__((used)) static int s390_next_event(unsigned long delta,
			   struct clock_event_device *evt)
{
	S390_lowcore.clock_comparator = get_tod_clock() + delta;
	set_clock_comparator(S390_lowcore.clock_comparator);
	return 0;
}
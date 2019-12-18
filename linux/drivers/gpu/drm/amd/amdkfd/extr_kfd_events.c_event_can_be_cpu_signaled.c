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
struct kfd_event {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ KFD_EVENT_TYPE_SIGNAL ; 

__attribute__((used)) static bool event_can_be_cpu_signaled(const struct kfd_event *ev)
{
	return ev->type == KFD_EVENT_TYPE_SIGNAL;
}
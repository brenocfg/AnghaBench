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
struct kfd_process {int /*<<< orphan*/  signal_page; } ;
struct kfd_event {size_t event_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNSIGNALED_EVENT_SLOT ; 
 int /*<<< orphan*/ * page_slots (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acknowledge_signal(struct kfd_process *p, struct kfd_event *ev)
{
	page_slots(p->signal_page)[ev->event_id] = UNSIGNALED_EVENT_SLOT;
}
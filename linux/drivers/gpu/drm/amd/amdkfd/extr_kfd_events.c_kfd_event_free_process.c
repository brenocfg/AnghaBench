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
struct kfd_process {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_events (struct kfd_process*) ; 
 int /*<<< orphan*/  shutdown_signal_page (struct kfd_process*) ; 

void kfd_event_free_process(struct kfd_process *p)
{
	destroy_events(p);
	shutdown_signal_page(p);
}
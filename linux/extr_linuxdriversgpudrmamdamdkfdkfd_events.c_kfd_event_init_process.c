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
struct kfd_process {scalar_t__ signal_event_count; int /*<<< orphan*/ * signal_page; int /*<<< orphan*/  event_idr; int /*<<< orphan*/  event_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void kfd_event_init_process(struct kfd_process *p)
{
	mutex_init(&p->event_mutex);
	idr_init(&p->event_idr);
	p->signal_page = NULL;
	p->signal_event_count = 0;
}
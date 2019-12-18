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
struct input_dev_poller {scalar_t__ poll_interval; int /*<<< orphan*/  input; int /*<<< orphan*/  (* poll ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  input_dev_poller_queue_work (struct input_dev_poller*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void input_dev_poller_start(struct input_dev_poller *poller)
{
	/* Only start polling if polling is enabled */
	if (poller->poll_interval > 0) {
		poller->poll(poller->input);
		input_dev_poller_queue_work(poller);
	}
}
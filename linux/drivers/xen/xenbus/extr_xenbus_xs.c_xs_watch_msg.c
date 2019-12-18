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
struct xs_watch_event {char const* path; char const* token; int /*<<< orphan*/  list; int /*<<< orphan*/ * handle; scalar_t__ body; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EINVAL ; 
 int count_strings (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_watch (char const*) ; 
 int /*<<< orphan*/  kfree (struct xs_watch_event*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (scalar_t__,char) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watch_events ; 
 int /*<<< orphan*/  watch_events_lock ; 
 int /*<<< orphan*/  watch_events_waitq ; 
 int /*<<< orphan*/  watches_lock ; 

int xs_watch_msg(struct xs_watch_event *event)
{
	if (count_strings(event->body, event->len) != 2) {
		kfree(event);
		return -EINVAL;
	}
	event->path = (const char *)event->body;
	event->token = (const char *)strchr(event->body, '\0') + 1;

	spin_lock(&watches_lock);
	event->handle = find_watch(event->token);
	if (event->handle != NULL) {
		spin_lock(&watch_events_lock);
		list_add_tail(&event->list, &watch_events);
		wake_up(&watch_events_waitq);
		spin_unlock(&watch_events_lock);
	} else
		kfree(event);
	spin_unlock(&watches_lock);

	return 0;
}
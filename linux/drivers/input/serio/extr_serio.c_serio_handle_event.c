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
struct work_struct {int dummy; } ;
struct serio_event {int type; int /*<<< orphan*/  object; } ;

/* Variables and functions */
#define  SERIO_ATTACH_DRIVER 132 
#define  SERIO_RECONNECT_PORT 131 
#define  SERIO_RECONNECT_SUBTREE 130 
#define  SERIO_REGISTER_PORT 129 
#define  SERIO_RESCAN_PORT 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_add_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_attach_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_disconnect_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_find_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_free_event (struct serio_event*) ; 
 struct serio_event* serio_get_event () ; 
 int /*<<< orphan*/  serio_mutex ; 
 int /*<<< orphan*/  serio_reconnect_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_reconnect_subtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_remove_duplicate_events (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void serio_handle_event(struct work_struct *work)
{
	struct serio_event *event;

	mutex_lock(&serio_mutex);

	while ((event = serio_get_event())) {

		switch (event->type) {

		case SERIO_REGISTER_PORT:
			serio_add_port(event->object);
			break;

		case SERIO_RECONNECT_PORT:
			serio_reconnect_port(event->object);
			break;

		case SERIO_RESCAN_PORT:
			serio_disconnect_port(event->object);
			serio_find_driver(event->object);
			break;

		case SERIO_RECONNECT_SUBTREE:
			serio_reconnect_subtree(event->object);
			break;

		case SERIO_ATTACH_DRIVER:
			serio_attach_driver(event->object);
			break;
		}

		serio_remove_duplicate_events(event->object, event->type);
		serio_free_event(event);
	}

	mutex_unlock(&serio_mutex);
}
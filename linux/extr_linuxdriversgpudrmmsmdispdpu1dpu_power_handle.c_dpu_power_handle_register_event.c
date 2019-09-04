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
typedef  scalar_t__ u32 ;
struct dpu_power_handle {int /*<<< orphan*/  phandle_lock; int /*<<< orphan*/  event_list; } ;
struct dpu_power_event {void (* cb_fnc ) (scalar_t__,void*) ;int active; int /*<<< orphan*/  list; int /*<<< orphan*/  client_name; void* usr; scalar_t__ event_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dpu_power_event* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_CLIENT_NAME_LEN ; 
 struct dpu_power_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct dpu_power_event *dpu_power_handle_register_event(
		struct dpu_power_handle *phandle,
		u32 event_type, void (*cb_fnc)(u32 event_type, void *usr),
		void *usr, char *client_name)
{
	struct dpu_power_event *event;

	if (!phandle) {
		pr_err("invalid power handle\n");
		return ERR_PTR(-EINVAL);
	} else if (!cb_fnc || !event_type) {
		pr_err("no callback fnc or event type\n");
		return ERR_PTR(-EINVAL);
	}

	event = kzalloc(sizeof(struct dpu_power_event), GFP_KERNEL);
	if (!event)
		return ERR_PTR(-ENOMEM);

	event->event_type = event_type;
	event->cb_fnc = cb_fnc;
	event->usr = usr;
	strlcpy(event->client_name, client_name, MAX_CLIENT_NAME_LEN);
	event->active = true;

	mutex_lock(&phandle->phandle_lock);
	list_add(&event->list, &phandle->event_list);
	mutex_unlock(&phandle->phandle_lock);

	return event;
}
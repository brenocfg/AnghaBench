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
typedef  int /*<<< orphan*/  u32 ;
struct zfcp_fc_event {int code; int /*<<< orphan*/  list; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  list; } ;
struct zfcp_adapter {TYPE_1__ events; int /*<<< orphan*/  work_queue; } ;
typedef  enum fc_host_event_code { ____Placeholder_fc_host_event_code } fc_host_event_code ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct zfcp_fc_event* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void zfcp_fc_enqueue_event(struct zfcp_adapter *adapter,
			   enum fc_host_event_code event_code, u32 event_data)
{
	struct zfcp_fc_event *event;

	event = kmalloc(sizeof(struct zfcp_fc_event), GFP_ATOMIC);
	if (!event)
		return;

	event->code = event_code;
	event->data = event_data;

	spin_lock(&adapter->events.list_lock);
	list_add_tail(&event->list, &adapter->events.list);
	spin_unlock(&adapter->events.list_lock);

	queue_work(adapter->work_queue, &adapter->events.work);
}
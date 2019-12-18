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
struct ath10k_qmi_driver_event {int type; int /*<<< orphan*/  list; void* data; } ;
struct ath10k_qmi {int /*<<< orphan*/  event_work; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_list; } ;
typedef  enum ath10k_qmi_driver_event_type { ____Placeholder_ath10k_qmi_driver_event_type } ath10k_qmi_driver_event_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ath10k_qmi_driver_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath10k_qmi_driver_event_post(struct ath10k_qmi *qmi,
			     enum ath10k_qmi_driver_event_type type,
			     void *data)
{
	struct ath10k_qmi_driver_event *event;

	event = kzalloc(sizeof(*event), GFP_ATOMIC);
	if (!event)
		return -ENOMEM;

	event->type = type;
	event->data = data;

	spin_lock(&qmi->event_lock);
	list_add_tail(&event->list, &qmi->event_list);
	spin_unlock(&qmi->event_lock);

	queue_work(qmi->event_wq, &qmi->event_work);

	return 0;
}
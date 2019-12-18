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
struct pqi_event_response {int /*<<< orphan*/  additional_event_id; int /*<<< orphan*/  event_id; int /*<<< orphan*/  event_type; scalar_t__ request_acknowlege; } ;
struct pqi_event_queue {int oq_ci_copy; int /*<<< orphan*/  oq_ci; struct pqi_event_response* oq_element_array; int /*<<< orphan*/  oq_pi; } ;
struct pqi_event {int pending; int /*<<< orphan*/  additional_event_id; int /*<<< orphan*/  event_id; int /*<<< orphan*/  event_type; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  event_work; struct pqi_event* events; struct pqi_event_queue event_queue; } ;
typedef  int pqi_index_t ;

/* Variables and functions */
 int PQI_EVENT_OQ_ELEMENT_LENGTH ; 
 int PQI_NUM_EVENT_QUEUE_ELEMENTS ; 
 int pqi_event_type_to_event_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_ofa_capture_event_payload (struct pqi_event*,struct pqi_event_response*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int pqi_process_event_intr(struct pqi_ctrl_info *ctrl_info)
{
	unsigned int num_events;
	pqi_index_t oq_pi;
	pqi_index_t oq_ci;
	struct pqi_event_queue *event_queue;
	struct pqi_event_response *response;
	struct pqi_event *event;
	int event_index;

	event_queue = &ctrl_info->event_queue;
	num_events = 0;
	oq_ci = event_queue->oq_ci_copy;

	while (1) {
		oq_pi = readl(event_queue->oq_pi);
		if (oq_pi == oq_ci)
			break;

		num_events++;
		response = event_queue->oq_element_array +
			(oq_ci * PQI_EVENT_OQ_ELEMENT_LENGTH);

		event_index =
			pqi_event_type_to_event_index(response->event_type);

		if (event_index >= 0) {
			if (response->request_acknowlege) {
				event = &ctrl_info->events[event_index];
				event->pending = true;
				event->event_type = response->event_type;
				event->event_id = response->event_id;
				event->additional_event_id =
					response->additional_event_id;
				pqi_ofa_capture_event_payload(event, response);
			}
		}

		oq_ci = (oq_ci + 1) % PQI_NUM_EVENT_QUEUE_ELEMENTS;
	}

	if (num_events) {
		event_queue->oq_ci_copy = oq_ci;
		writel(oq_ci, event_queue->oq_ci);
		schedule_work(&ctrl_info->event_work);
	}

	return num_events;
}
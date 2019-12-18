#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int /*<<< orphan*/  reason; } ;
struct TYPE_4__ {int /*<<< orphan*/  bytes_requested; } ;
struct TYPE_6__ {TYPE_2__ ofa_cancelled; TYPE_1__ ofa_memory_allocation; } ;
struct pqi_event_response {TYPE_3__ data; } ;
struct pqi_event {scalar_t__ event_type; int /*<<< orphan*/  ofa_cancel_reason; int /*<<< orphan*/  ofa_bytes_requested; int /*<<< orphan*/  event_id; } ;

/* Variables and functions */
 scalar_t__ PQI_EVENT_OFA_CANCELLED ; 
 scalar_t__ PQI_EVENT_OFA_MEMORY_ALLOCATION ; 
 scalar_t__ PQI_EVENT_TYPE_OFA ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pqi_ofa_capture_event_payload(struct pqi_event *event,
	struct pqi_event_response *response)
{
	u16 event_id;

	event_id = get_unaligned_le16(&event->event_id);

	if (event->event_type == PQI_EVENT_TYPE_OFA) {
		if (event_id == PQI_EVENT_OFA_MEMORY_ALLOCATION) {
			event->ofa_bytes_requested =
			response->data.ofa_memory_allocation.bytes_requested;
		} else if (event_id == PQI_EVENT_OFA_CANCELLED) {
			event->ofa_cancel_reason =
			response->data.ofa_cancelled.reason;
		}
	}
}
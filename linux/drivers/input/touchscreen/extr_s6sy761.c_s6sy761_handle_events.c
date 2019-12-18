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
typedef  int u8 ;
struct s6sy761_data {int* data; } ;

/* Variables and functions */
#define  S6SY761_EVENT_ID_COORDINATE 129 
#define  S6SY761_EVENT_ID_STATUS 128 
 int S6SY761_EVENT_SIZE ; 
 int S6SY761_MASK_EID ; 
 int /*<<< orphan*/  s6sy761_handle_coordinates (struct s6sy761_data*,int*) ; 

__attribute__((used)) static void s6sy761_handle_events(struct s6sy761_data *sdata, u8 n_events)
{
	int i;

	for (i = 0; i < n_events; i++) {
		u8 *event = &sdata->data[i * S6SY761_EVENT_SIZE];
		u8 event_id = event[0] & S6SY761_MASK_EID;

		if (!event[0])
			return;

		switch (event_id) {

		case S6SY761_EVENT_ID_COORDINATE:
			s6sy761_handle_coordinates(sdata, event);
			break;

		case S6SY761_EVENT_ID_STATUS:
			break;

		default:
			break;
		}
	}
}
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
struct mma9553_data {int num_events; TYPE_1__* events; } ;
struct TYPE_2__ {int enabled; int /*<<< orphan*/ * info; } ;

/* Variables and functions */
 int MMA9553_EVENTS_INFO_SIZE ; 
 int /*<<< orphan*/ * mma9553_events_info ; 

__attribute__((used)) static void mma9553_init_events(struct mma9553_data *data)
{
	int i;

	data->num_events = MMA9553_EVENTS_INFO_SIZE;
	for (i = 0; i < data->num_events; i++) {
		data->events[i].info = &mma9553_events_info[i];
		data->events[i].enabled = false;
	}
}
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
struct mma9553_event {TYPE_1__* info; } ;
struct mma9553_data {int num_events; struct mma9553_event* events; } ;
typedef  enum iio_modifier { ____Placeholder_iio_modifier } iio_modifier ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;
struct TYPE_2__ {int type; int mod; int dir; } ;

/* Variables and functions */

__attribute__((used)) static struct mma9553_event *mma9553_get_event(struct mma9553_data *data,
					       enum iio_chan_type type,
					       enum iio_modifier mod,
					       enum iio_event_direction dir)
{
	int i;

	for (i = 0; i < data->num_events; i++)
		if (data->events[i].info->type == type &&
		    data->events[i].info->mod == mod &&
		    data->events[i].info->dir == dir)
			return &data->events[i];

	return NULL;
}
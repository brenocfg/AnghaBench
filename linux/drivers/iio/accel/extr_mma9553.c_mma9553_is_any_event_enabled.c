#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mma9553_data {int num_events; TYPE_2__* events; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;
struct TYPE_4__ {scalar_t__ enabled; TYPE_1__* info; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */

__attribute__((used)) static bool mma9553_is_any_event_enabled(struct mma9553_data *data,
					 bool check_type,
					 enum iio_chan_type type)
{
	int i;

	for (i = 0; i < data->num_events; i++)
		if ((check_type && data->events[i].info->type == type &&
		     data->events[i].enabled) ||
		     (!check_type && data->events[i].enabled))
			return true;

	return false;
}
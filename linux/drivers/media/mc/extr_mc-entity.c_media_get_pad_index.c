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
struct media_entity {int num_pads; TYPE_1__* pads; } ;
typedef  enum media_pad_signal_type { ____Placeholder_media_pad_signal_type } media_pad_signal_type ;
struct TYPE_2__ {scalar_t__ flags; int sig_type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_PAD_FL_SINK ; 
 scalar_t__ MEDIA_PAD_FL_SOURCE ; 

int media_get_pad_index(struct media_entity *entity, bool is_sink,
			enum media_pad_signal_type sig_type)
{
	int i;
	bool pad_is_sink;

	if (!entity)
		return -EINVAL;

	for (i = 0; i < entity->num_pads; i++) {
		if (entity->pads[i].flags == MEDIA_PAD_FL_SINK)
			pad_is_sink = true;
		else if (entity->pads[i].flags == MEDIA_PAD_FL_SOURCE)
			pad_is_sink = false;
		else
			continue;	/* This is an error! */

		if (pad_is_sink != is_sink)
			continue;
		if (entity->pads[i].sig_type == sig_type)
			return i;
	}
	return -EINVAL;
}
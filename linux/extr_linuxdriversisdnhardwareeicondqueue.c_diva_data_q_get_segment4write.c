#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int segment_pending; scalar_t__ count; scalar_t__ segments; void** data; size_t write; } ;
typedef  TYPE_1__ diva_um_idi_data_queue_t ;

/* Variables and functions */

void *diva_data_q_get_segment4write(diva_um_idi_data_queue_t *q)
{
	if ((!q->segment_pending) && (q->count < q->segments)) {
		q->segment_pending = 1;
		return (q->data[q->write]);
	}

	return NULL;
}
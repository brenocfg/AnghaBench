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
struct TYPE_3__ {int* length; size_t write; size_t segments; scalar_t__ segment_pending; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ diva_um_idi_data_queue_t ;

/* Variables and functions */

void
diva_data_q_ack_segment4write(diva_um_idi_data_queue_t *q, int length)
{
	if (q->segment_pending) {
		q->length[q->write] = length;
		q->count++;
		q->write++;
		if (q->write >= q->segments) {
			q->write = 0;
		}
		q->segment_pending = 0;
	}
}
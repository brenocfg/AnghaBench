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
typedef  scalar_t__ u64 ;
struct vb2_queue {unsigned int num_buffers; TYPE_1__** bufs; } ;
struct TYPE_2__ {scalar_t__ timestamp; scalar_t__ copied_timestamp; } ;

/* Variables and functions */

int vb2_find_timestamp(const struct vb2_queue *q, u64 timestamp,
		       unsigned int start_idx)
{
	unsigned int i;

	for (i = start_idx; i < q->num_buffers; i++)
		if (q->bufs[i]->copied_timestamp &&
		    q->bufs[i]->timestamp == timestamp)
			return i;
	return -1;
}
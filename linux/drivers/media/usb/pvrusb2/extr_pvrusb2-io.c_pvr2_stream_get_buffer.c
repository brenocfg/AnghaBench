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
struct pvr2_stream {int buffer_total_count; struct pvr2_buffer** buffers; } ;
struct pvr2_buffer {int dummy; } ;

/* Variables and functions */

struct pvr2_buffer *pvr2_stream_get_buffer(struct pvr2_stream *sp, int id)
{
	if (id < 0) return NULL;
	if (id >= sp->buffer_total_count) return NULL;
	return sp->buffers[id];
}
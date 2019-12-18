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
struct videobuf_queue {void* last; void* field; struct cx18_stream* priv_data; } ;
struct cx18_stream {struct cx18* cx; } ;
struct TYPE_2__ {int width; int height; } ;
struct cx18 {TYPE_1__ cxhdl; } ;

/* Variables and functions */
 void* V4L2_FIELD_INTERLACED ; 
 unsigned int VB_MIN_BUFFERS ; 
 unsigned int VB_MIN_BUFSIZE ; 

__attribute__((used)) static int buffer_setup(struct videobuf_queue *q,
	unsigned int *count, unsigned int *size)
{
	struct cx18_stream *s = q->priv_data;
	struct cx18 *cx = s->cx;

	*size = 2 * cx->cxhdl.width * cx->cxhdl.height;
	if (*count == 0)
		*count = VB_MIN_BUFFERS;

	while (*size * *count > VB_MIN_BUFFERS * VB_MIN_BUFSIZE)
		(*count)--;

	q->field = V4L2_FIELD_INTERLACED;
	q->last = V4L2_FIELD_INTERLACED;

	return 0;
}
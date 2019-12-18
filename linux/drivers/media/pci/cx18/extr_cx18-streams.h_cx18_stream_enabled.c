#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ v4l2_dev; } ;
struct cx18_stream {size_t type; TYPE_3__* cx; TYPE_2__* dvb; TYPE_1__ video_dev; } ;
struct TYPE_6__ {scalar_t__* stream_buffers; } ;
struct TYPE_5__ {scalar_t__ enabled; } ;

/* Variables and functions */
 size_t CX18_ENC_STREAM_TYPE_IDX ; 

__attribute__((used)) static inline bool cx18_stream_enabled(struct cx18_stream *s)
{
	return s->video_dev.v4l2_dev ||
	       (s->dvb && s->dvb->enabled) ||
	       (s->type == CX18_ENC_STREAM_TYPE_IDX &&
		s->cx->stream_buffers[CX18_ENC_STREAM_TYPE_IDX] != 0);
}
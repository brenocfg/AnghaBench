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
struct cx18_stream {int /*<<< orphan*/  s_flags; } ;
struct cx18 {struct cx18_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int CX18_MAX_STREAMS ; 
 int /*<<< orphan*/  cx18_stop_v4l2_encode_stream (struct cx18_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_stream_enabled (struct cx18_stream*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cx18_stop_all_captures(struct cx18 *cx)
{
	int i;

	for (i = CX18_MAX_STREAMS - 1; i >= 0; i--) {
		struct cx18_stream *s = &cx->streams[i];

		if (!cx18_stream_enabled(s))
			continue;
		if (test_bit(CX18_F_S_STREAMING, &s->s_flags))
			cx18_stop_v4l2_encode_stream(s, 0);
	}
}
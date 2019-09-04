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
struct TYPE_2__ {int /*<<< orphan*/ * v4l2_dev; } ;
struct ivtv_stream {int /*<<< orphan*/  s_flags; TYPE_1__ vdev; } ;
struct ivtv {struct ivtv_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_F_S_STREAMING ; 
 int IVTV_MAX_STREAMS ; 
 int /*<<< orphan*/  ivtv_stop_v4l2_encode_stream (struct ivtv_stream*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ivtv_stop_all_captures(struct ivtv *itv)
{
	int i;

	for (i = IVTV_MAX_STREAMS - 1; i >= 0; i--) {
		struct ivtv_stream *s = &itv->streams[i];

		if (s->vdev.v4l2_dev == NULL)
			continue;
		if (test_bit(IVTV_F_S_STREAMING, &s->s_flags)) {
			ivtv_stop_v4l2_encode_stream(s, 0);
		}
	}
}
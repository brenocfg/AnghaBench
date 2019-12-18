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
struct video_device {int dummy; } ;
struct cobalt_stream {int /*<<< orphan*/  is_dummy; int /*<<< orphan*/  is_audio; struct video_device vdev; } ;
struct cobalt {struct cobalt_stream* streams; } ;

/* Variables and functions */
 int COBALT_NUM_STREAMS ; 
 int /*<<< orphan*/  cobalt_alsa_exit (struct cobalt_stream*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

void cobalt_nodes_unregister(struct cobalt *cobalt)
{
	int node;

	/* Teardown all streams */
	for (node = 0; node < COBALT_NUM_STREAMS; node++) {
		struct cobalt_stream *s = cobalt->streams + node;
		struct video_device *vdev = &s->vdev;

		if (!s->is_audio)
			video_unregister_device(vdev);
		else if (!s->is_dummy)
			cobalt_alsa_exit(s);
	}
}
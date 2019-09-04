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
struct video_device {int /*<<< orphan*/ * v4l2_dev; } ;
struct cx18 {scalar_t__* stream_buffers; TYPE_1__* streams; } ;
struct TYPE_3__ {scalar_t__ buffers; int /*<<< orphan*/  vbuf_q; struct video_device video_dev; int /*<<< orphan*/ * dvb; } ;

/* Variables and functions */
 int CX18_ENC_STREAM_TYPE_IDX ; 
 int CX18_ENC_STREAM_TYPE_TS ; 
 int CX18_ENC_STREAM_TYPE_YUV ; 
 int CX18_MAX_STREAMS ; 
 int /*<<< orphan*/  cx18_dvb_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  cx18_stream_free (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 

void cx18_streams_cleanup(struct cx18 *cx, int unregister)
{
	struct video_device *vdev;
	int type;

	/* Teardown all streams */
	for (type = 0; type < CX18_MAX_STREAMS; type++) {

		/* The TS has a cx18_dvb structure, not a video_device */
		if (type == CX18_ENC_STREAM_TYPE_TS) {
			if (cx->streams[type].dvb != NULL) {
				if (unregister)
					cx18_dvb_unregister(&cx->streams[type]);
				kfree(cx->streams[type].dvb);
				cx->streams[type].dvb = NULL;
				cx18_stream_free(&cx->streams[type]);
			}
			continue;
		}

		/* No struct video_device, but can have buffers allocated */
		if (type == CX18_ENC_STREAM_TYPE_IDX) {
			/* If the module params didn't inhibit IDX ... */
			if (cx->stream_buffers[type] != 0) {
				cx->stream_buffers[type] = 0;
				/*
				 * Before calling cx18_stream_free(),
				 * check if the IDX stream was actually set up.
				 * Needed, since the cx18_probe() error path
				 * exits through here as well as normal clean up
				 */
				if (cx->streams[type].buffers != 0)
					cx18_stream_free(&cx->streams[type]);
			}
			continue;
		}

		/* If struct video_device exists, can have buffers allocated */
		vdev = &cx->streams[type].video_dev;

		if (vdev->v4l2_dev == NULL)
			continue;

		if (type == CX18_ENC_STREAM_TYPE_YUV)
			videobuf_mmap_free(&cx->streams[type].vbuf_q);

		cx18_stream_free(&cx->streams[type]);

		video_unregister_device(vdev);
	}
}
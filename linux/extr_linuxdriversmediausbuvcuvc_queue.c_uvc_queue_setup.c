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
struct vb2_queue {int type; } ;
struct uvc_video_queue {int dummy; } ;
struct TYPE_2__ {unsigned int dwMaxVideoFrameSize; } ;
struct uvc_streaming {TYPE_1__ ctrl; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int UVC_METATADA_BUF_SIZE ; 
#define  V4L2_BUF_TYPE_META_CAPTURE 128 
 struct uvc_streaming* uvc_queue_to_stream (struct uvc_video_queue*) ; 
 struct uvc_video_queue* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int uvc_queue_setup(struct vb2_queue *vq,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct uvc_video_queue *queue = vb2_get_drv_priv(vq);
	struct uvc_streaming *stream;
	unsigned int size;

	switch (vq->type) {
	case V4L2_BUF_TYPE_META_CAPTURE:
		size = UVC_METATADA_BUF_SIZE;
		break;

	default:
		stream = uvc_queue_to_stream(queue);
		size = stream->ctrl.dwMaxVideoFrameSize;
		break;
	}

	/*
	 * When called with plane sizes, validate them. The driver supports
	 * single planar formats only, and requires buffers to be large enough
	 * to store a complete frame.
	 */
	if (*nplanes)
		return *nplanes != 1 || sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;
	return 0;
}
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
struct media_entity {struct media_pad* pads; } ;
struct video_device {struct media_entity entity; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct media_pad {int flags; struct media_entity* entity; } ;
struct camss_video {TYPE_1__* ops; int /*<<< orphan*/  pipe; struct video_device vdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_buffers ) (struct camss_video*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int media_pipeline_start (struct media_entity*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (struct media_entity*) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  stub1 (struct camss_video*,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,struct camss_video*,int /*<<< orphan*/ ,int) ; 
 struct camss_video* vb2_get_drv_priv (struct vb2_queue*) ; 
 int video_check_format (struct camss_video*) ; 

__attribute__((used)) static int video_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct camss_video *video = vb2_get_drv_priv(q);
	struct video_device *vdev = &video->vdev;
	struct media_entity *entity;
	struct media_pad *pad;
	struct v4l2_subdev *subdev;
	int ret;

	ret = media_pipeline_start(&vdev->entity, &video->pipe);
	if (ret < 0)
		return ret;

	ret = video_check_format(video);
	if (ret < 0)
		goto error;

	entity = &vdev->entity;
	while (1) {
		pad = &entity->pads[0];
		if (!(pad->flags & MEDIA_PAD_FL_SINK))
			break;

		pad = media_entity_remote_pad(pad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			break;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		ret = v4l2_subdev_call(subdev, video, s_stream, 1);
		if (ret < 0 && ret != -ENOIOCTLCMD)
			goto error;
	}

	return 0;

error:
	media_pipeline_stop(&vdev->entity);

	video->ops->flush_buffers(video, VB2_BUF_STATE_QUEUED);

	return ret;
}
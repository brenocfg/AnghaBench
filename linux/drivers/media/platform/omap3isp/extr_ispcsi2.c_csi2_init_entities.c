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
struct media_entity {int /*<<< orphan*/ * ops; } ;
struct v4l2_subdev {int grp_id; struct media_entity entity; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * internal_ops; } ;
struct media_pad {int flags; } ;
struct TYPE_2__ {int bpl_alignment; int bpl_zero_padding; int bpl_max; int capture_mem; int /*<<< orphan*/  isp; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; } ;
struct isp_csi2_device {struct v4l2_subdev subdev; TYPE_1__ video_out; int /*<<< orphan*/  isp; struct media_pad* pads; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_PADS_NUM ; 
 size_t CSI2_PAD_SINK ; 
 size_t CSI2_PAD_SOURCE ; 
 int MEDIA_PAD_FL_MUST_CONNECT ; 
 int MEDIA_PAD_FL_SINK ; 
 int MEDIA_PAD_FL_SOURCE ; 
 int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  csi2_init_formats (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csi2_internal_ops ; 
 int /*<<< orphan*/  csi2_ispvideo_ops ; 
 int /*<<< orphan*/  csi2_media_ops ; 
 int /*<<< orphan*/  csi2_ops ; 
 int /*<<< orphan*/  media_entity_cleanup (struct media_entity*) ; 
 int media_entity_pads_init (struct media_entity*,int /*<<< orphan*/ ,struct media_pad*) ; 
 int omap3isp_video_init (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct isp_csi2_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int csi2_init_entities(struct isp_csi2_device *csi2)
{
	struct v4l2_subdev *sd = &csi2->subdev;
	struct media_pad *pads = csi2->pads;
	struct media_entity *me = &sd->entity;
	int ret;

	v4l2_subdev_init(sd, &csi2_ops);
	sd->internal_ops = &csi2_internal_ops;
	strscpy(sd->name, "OMAP3 ISP CSI2a", sizeof(sd->name));

	sd->grp_id = 1 << 16;	/* group ID for isp subdevs */
	v4l2_set_subdevdata(sd, csi2);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[CSI2_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	pads[CSI2_PAD_SINK].flags = MEDIA_PAD_FL_SINK
				    | MEDIA_PAD_FL_MUST_CONNECT;

	me->ops = &csi2_media_ops;
	ret = media_entity_pads_init(me, CSI2_PADS_NUM, pads);
	if (ret < 0)
		return ret;

	csi2_init_formats(sd, NULL);

	/* Video device node */
	csi2->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	csi2->video_out.ops = &csi2_ispvideo_ops;
	csi2->video_out.bpl_alignment = 32;
	csi2->video_out.bpl_zero_padding = 1;
	csi2->video_out.bpl_max = 0x1ffe0;
	csi2->video_out.isp = csi2->isp;
	csi2->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;

	ret = omap3isp_video_init(&csi2->video_out, "CSI2a");
	if (ret < 0)
		goto error_video;

	return 0;

error_video:
	media_entity_cleanup(&csi2->subdev.entity);
	return ret;
}
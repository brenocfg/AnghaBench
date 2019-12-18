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
struct v4l2_subdev {char* name; struct media_entity entity; int /*<<< orphan*/  flags; int /*<<< orphan*/  grp_id; int /*<<< orphan*/ * internal_ops; } ;
struct media_pad {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int bpl_alignment; int bpl_zero_padding; int bpl_max; int capture_mem; int /*<<< orphan*/  iss; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; } ;
struct iss_csi2_device {struct v4l2_subdev subdev; TYPE_1__ video_out; int /*<<< orphan*/  iss; struct media_pad* pads; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CSI2_PADS_NUM ; 
 size_t CSI2_PAD_SINK ; 
 size_t CSI2_PAD_SOURCE ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_NAME_SIZE ; 
 int /*<<< orphan*/  csi2_init_formats (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csi2_internal_ops ; 
 int /*<<< orphan*/  csi2_issvideo_ops ; 
 int /*<<< orphan*/  csi2_media_ops ; 
 int /*<<< orphan*/  csi2_ops ; 
 int /*<<< orphan*/  media_entity_cleanup (struct media_entity*) ; 
 int media_entity_pads_init (struct media_entity*,int /*<<< orphan*/ ,struct media_pad*) ; 
 int omap4iss_video_init (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct iss_csi2_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int csi2_init_entities(struct iss_csi2_device *csi2, const char *subname)
{
	struct v4l2_subdev *sd = &csi2->subdev;
	struct media_pad *pads = csi2->pads;
	struct media_entity *me = &sd->entity;
	int ret;
	char name[V4L2_SUBDEV_NAME_SIZE];

	v4l2_subdev_init(sd, &csi2_ops);
	sd->internal_ops = &csi2_internal_ops;
	snprintf(name, sizeof(name), "CSI2%s", subname);
	snprintf(sd->name, sizeof(sd->name), "OMAP4 ISS %s", name);

	sd->grp_id = BIT(16);	/* group ID for iss subdevs */
	v4l2_set_subdevdata(sd, csi2);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[CSI2_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	pads[CSI2_PAD_SINK].flags = MEDIA_PAD_FL_SINK;

	me->ops = &csi2_media_ops;
	ret = media_entity_pads_init(me, CSI2_PADS_NUM, pads);
	if (ret < 0)
		return ret;

	csi2_init_formats(sd, NULL);

	/* Video device node */
	csi2->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	csi2->video_out.ops = &csi2_issvideo_ops;
	csi2->video_out.bpl_alignment = 32;
	csi2->video_out.bpl_zero_padding = 1;
	csi2->video_out.bpl_max = 0x1ffe0;
	csi2->video_out.iss = csi2->iss;
	csi2->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;

	ret = omap4iss_video_init(&csi2->video_out, name);
	if (ret < 0)
		goto error_video;

	return 0;

error_video:
	media_entity_cleanup(&csi2->subdev.entity);
	return ret;
}
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
struct v4l2_subdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  name; int /*<<< orphan*/ * internal_ops; struct media_entity entity; } ;
struct media_pad {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int capture_mem; int bpl_alignment; int bpl_zero_padding; int bpl_max; int /*<<< orphan*/  iss; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; } ;
struct iss_resizer_device {TYPE_1__ video_out; int /*<<< orphan*/  input; struct media_pad* pads; struct v4l2_subdev subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  RESIZER_INPUT_NONE ; 
 int /*<<< orphan*/  RESIZER_PADS_NUM ; 
 size_t RESIZER_PAD_SINK ; 
 size_t RESIZER_PAD_SOURCE_MEM ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int media_entity_pads_init (struct media_entity*,int /*<<< orphan*/ ,struct media_pad*) ; 
 int omap4iss_video_init (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  resizer_init_formats (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resizer_media_ops ; 
 int /*<<< orphan*/  resizer_v4l2_internal_ops ; 
 int /*<<< orphan*/  resizer_v4l2_ops ; 
 int /*<<< orphan*/  resizer_video_ops ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  to_iss_device (struct iss_resizer_device*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct iss_resizer_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int resizer_init_entities(struct iss_resizer_device *resizer)
{
	struct v4l2_subdev *sd = &resizer->subdev;
	struct media_pad *pads = resizer->pads;
	struct media_entity *me = &sd->entity;
	int ret;

	resizer->input = RESIZER_INPUT_NONE;

	v4l2_subdev_init(sd, &resizer_v4l2_ops);
	sd->internal_ops = &resizer_v4l2_internal_ops;
	strscpy(sd->name, "OMAP4 ISS ISP resizer", sizeof(sd->name));
	sd->grp_id = BIT(16);	/* group ID for iss subdevs */
	v4l2_set_subdevdata(sd, resizer);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[RESIZER_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[RESIZER_PAD_SOURCE_MEM].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &resizer_media_ops;
	ret = media_entity_pads_init(me, RESIZER_PADS_NUM, pads);
	if (ret < 0)
		return ret;

	resizer_init_formats(sd, NULL);

	resizer->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	resizer->video_out.ops = &resizer_video_ops;
	resizer->video_out.iss = to_iss_device(resizer);
	resizer->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;
	resizer->video_out.bpl_alignment = 32;
	resizer->video_out.bpl_zero_padding = 1;
	resizer->video_out.bpl_max = 0x1ffe0;

	return omap4iss_video_init(&resizer->video_out, "ISP resizer a");
}
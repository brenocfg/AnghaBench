#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {struct v4l2_ctrl_handler* ctrl_handler; int /*<<< orphan*/  entity; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct v4l2_ctrl_handler {int error; } ;
struct camif_dev {int /*<<< orphan*/  ctrl_colorfx; TYPE_1__* variant; int /*<<< orphan*/  ctrl_colorfx_cbcr; int /*<<< orphan*/  ctrl_test_pattern; TYPE_2__* pads; struct v4l2_subdev subdev; struct v4l2_ctrl_handler ctrl_handler; } ;
struct TYPE_4__ {void* flags; } ;
struct TYPE_3__ {scalar_t__ has_img_effect; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAMIF_SD_PADS_NUM ; 
 size_t CAMIF_SD_PAD_SINK ; 
 size_t CAMIF_SD_PAD_SOURCE_C ; 
 size_t CAMIF_SD_PAD_SOURCE_P ; 
 void* MEDIA_PAD_FL_SINK ; 
 void* MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_CID_COLORFX ; 
 int /*<<< orphan*/  V4L2_CID_COLORFX_CBCR ; 
 int /*<<< orphan*/  V4L2_CID_TEST_PATTERN ; 
 int /*<<< orphan*/  V4L2_COLORFX_NONE ; 
 int /*<<< orphan*/  V4L2_COLORFX_SET_CBCR ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  s3c_camif_subdev_ctrl_ops ; 
 int /*<<< orphan*/  s3c_camif_subdev_ops ; 
 int /*<<< orphan*/  s3c_camif_test_pattern_menu ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct camif_dev*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

int s3c_camif_create_subdev(struct camif_dev *camif)
{
	struct v4l2_ctrl_handler *handler = &camif->ctrl_handler;
	struct v4l2_subdev *sd = &camif->subdev;
	int ret;

	v4l2_subdev_init(sd, &s3c_camif_subdev_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	strscpy(sd->name, "S3C-CAMIF", sizeof(sd->name));

	camif->pads[CAMIF_SD_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	camif->pads[CAMIF_SD_PAD_SOURCE_C].flags = MEDIA_PAD_FL_SOURCE;
	camif->pads[CAMIF_SD_PAD_SOURCE_P].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&sd->entity, CAMIF_SD_PADS_NUM,
				camif->pads);
	if (ret)
		return ret;

	v4l2_ctrl_handler_init(handler, 3);
	camif->ctrl_test_pattern = v4l2_ctrl_new_std_menu_items(handler,
			&s3c_camif_subdev_ctrl_ops, V4L2_CID_TEST_PATTERN,
			ARRAY_SIZE(s3c_camif_test_pattern_menu) - 1, 0, 0,
			s3c_camif_test_pattern_menu);

	if (camif->variant->has_img_effect) {
		camif->ctrl_colorfx = v4l2_ctrl_new_std_menu(handler,
				&s3c_camif_subdev_ctrl_ops,
				V4L2_CID_COLORFX, V4L2_COLORFX_SET_CBCR,
				~0x981f, V4L2_COLORFX_NONE);

		camif->ctrl_colorfx_cbcr = v4l2_ctrl_new_std(handler,
				&s3c_camif_subdev_ctrl_ops,
				V4L2_CID_COLORFX_CBCR, 0, 0xffff, 1, 0);
	}

	if (handler->error) {
		v4l2_ctrl_handler_free(handler);
		media_entity_cleanup(&sd->entity);
		return handler->error;
	}

	if (camif->variant->has_img_effect)
		v4l2_ctrl_auto_cluster(2, &camif->ctrl_colorfx,
			       V4L2_COLORFX_SET_CBCR, false);

	sd->ctrl_handler = handler;
	v4l2_set_subdevdata(sd, camif);

	return 0;
}
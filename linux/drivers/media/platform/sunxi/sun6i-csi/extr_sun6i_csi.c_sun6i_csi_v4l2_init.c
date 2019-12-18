#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct v4l2_async_subdev {int dummy; } ;
struct TYPE_12__ {scalar_t__ hw_revision; int /*<<< orphan*/  model; int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ctrl_handler; TYPE_8__* mdev; } ;
struct sun6i_csi {TYPE_8__ media_dev; TYPE_4__ notifier; int /*<<< orphan*/  ctrl_handler; TYPE_1__ v4l2_dev; int /*<<< orphan*/  video; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  media_device_cleanup (TYPE_8__*) ; 
 int /*<<< orphan*/  media_device_init (TYPE_8__*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sun6i_csi_async_ops ; 
 int /*<<< orphan*/  sun6i_csi_fwnode_parse ; 
 int /*<<< orphan*/  sun6i_video_cleanup (int /*<<< orphan*/ *) ; 
 int sun6i_video_init (int /*<<< orphan*/ *,struct sun6i_csi*,char*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_4__*) ; 
 int v4l2_async_notifier_parse_fwnode_endpoints (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_register (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int v4l2_device_register (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 

__attribute__((used)) static int sun6i_csi_v4l2_init(struct sun6i_csi *csi)
{
	int ret;

	csi->media_dev.dev = csi->dev;
	strscpy(csi->media_dev.model, "Allwinner Video Capture Device",
		sizeof(csi->media_dev.model));
	csi->media_dev.hw_revision = 0;

	media_device_init(&csi->media_dev);
	v4l2_async_notifier_init(&csi->notifier);

	ret = v4l2_ctrl_handler_init(&csi->ctrl_handler, 0);
	if (ret) {
		dev_err(csi->dev, "V4L2 controls handler init failed (%d)\n",
			ret);
		goto clean_media;
	}

	csi->v4l2_dev.mdev = &csi->media_dev;
	csi->v4l2_dev.ctrl_handler = &csi->ctrl_handler;
	ret = v4l2_device_register(csi->dev, &csi->v4l2_dev);
	if (ret) {
		dev_err(csi->dev, "V4L2 device registration failed (%d)\n",
			ret);
		goto free_ctrl;
	}

	ret = sun6i_video_init(&csi->video, csi, "sun6i-csi");
	if (ret)
		goto unreg_v4l2;

	ret = v4l2_async_notifier_parse_fwnode_endpoints(csi->dev,
							 &csi->notifier,
							 sizeof(struct v4l2_async_subdev),
							 sun6i_csi_fwnode_parse);
	if (ret)
		goto clean_video;

	csi->notifier.ops = &sun6i_csi_async_ops;

	ret = v4l2_async_notifier_register(&csi->v4l2_dev, &csi->notifier);
	if (ret) {
		dev_err(csi->dev, "notifier registration failed\n");
		goto clean_video;
	}

	return 0;

clean_video:
	sun6i_video_cleanup(&csi->video);
unreg_v4l2:
	v4l2_device_unregister(&csi->v4l2_dev);
free_ctrl:
	v4l2_ctrl_handler_free(&csi->ctrl_handler);
clean_media:
	v4l2_async_notifier_cleanup(&csi->notifier);
	media_device_cleanup(&csi->media_dev);

	return ret;
}
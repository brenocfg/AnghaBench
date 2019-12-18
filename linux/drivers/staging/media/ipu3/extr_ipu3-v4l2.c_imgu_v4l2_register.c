#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ctrl_handler; int /*<<< orphan*/ * mdev; } ;
struct imgu_device {int streaming; int /*<<< orphan*/  media_dev; TYPE_1__ v4l2_dev; TYPE_4__* pci_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGU_MAX_PIPE_NUM ; 
 int /*<<< orphan*/  IMGU_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  imgu_v4l2_cleanup_pipes (struct imgu_device*,int /*<<< orphan*/ ) ; 
 int imgu_v4l2_register_pipes (struct imgu_device*) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_pci_init (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int media_device_register (int /*<<< orphan*/ *) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int v4l2_device_register_subdev_nodes (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 

int imgu_v4l2_register(struct imgu_device *imgu)
{
	int r;

	/* Initialize miscellaneous variables */
	imgu->streaming = false;

	/* Set up media device */
	media_device_pci_init(&imgu->media_dev, imgu->pci_dev, IMGU_NAME);

	/* Set up v4l2 device */
	imgu->v4l2_dev.mdev = &imgu->media_dev;
	imgu->v4l2_dev.ctrl_handler = NULL;
	r = v4l2_device_register(&imgu->pci_dev->dev, &imgu->v4l2_dev);
	if (r) {
		dev_err(&imgu->pci_dev->dev,
			"failed to register V4L2 device (%d)\n", r);
		goto fail_v4l2_dev;
	}

	r = imgu_v4l2_register_pipes(imgu);
	if (r) {
		dev_err(&imgu->pci_dev->dev,
			"failed to register pipes (%d)\n", r);
		goto fail_v4l2_pipes;
	}

	r = v4l2_device_register_subdev_nodes(&imgu->v4l2_dev);
	if (r) {
		dev_err(&imgu->pci_dev->dev,
			"failed to register subdevs (%d)\n", r);
		goto fail_subdevs;
	}

	r = media_device_register(&imgu->media_dev);
	if (r) {
		dev_err(&imgu->pci_dev->dev,
			"failed to register media device (%d)\n", r);
		goto fail_subdevs;
	}

	return 0;

fail_subdevs:
	imgu_v4l2_cleanup_pipes(imgu, IMGU_MAX_PIPE_NUM);
fail_v4l2_pipes:
	v4l2_device_unregister(&imgu->v4l2_dev);
fail_v4l2_dev:
	media_device_cleanup(&imgu->media_dev);

	return r;
}
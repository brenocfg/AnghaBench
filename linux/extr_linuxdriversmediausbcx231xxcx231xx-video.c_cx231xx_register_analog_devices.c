#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_5__* ctrl_handler; } ;
struct TYPE_17__ {int error; } ;
struct cx231xx {size_t devno; size_t model; TYPE_3__ radio_dev; int /*<<< orphan*/  dev; TYPE_5__ radio_ctrl_handler; TYPE_3__ vbi_dev; TYPE_5__ ctrl_handler; TYPE_3__ vdev; TYPE_1__* sd_cx25840; int /*<<< orphan*/  norm; int /*<<< orphan*/  video_input; int /*<<< orphan*/ * format; scalar_t__ interlaced; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
struct TYPE_15__ {scalar_t__ type; } ;
struct TYPE_14__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_13__ {TYPE_2__ radio; } ;

/* Variables and functions */
 scalar_t__ CX231XX_RADIO ; 
 int /*<<< orphan*/  CX231XX_VERSION ; 
 int /*<<< orphan*/  V4L2_STD_PAL ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  VFL_TYPE_VBI ; 
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_12__* cx231xx_boards ; 
 TYPE_7__ cx231xx_radio_template ; 
 TYPE_7__ cx231xx_vbi_template ; 
 int /*<<< orphan*/  cx231xx_vdev_init (struct cx231xx*,TYPE_3__*,TYPE_7__*,char*) ; 
 TYPE_7__ cx231xx_video_template ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * format ; 
 int /*<<< orphan*/  norm_maxh (struct cx231xx*) ; 
 int /*<<< orphan*/  norm_maxw (struct cx231xx*) ; 
 int /*<<< orphan*/ * radio_nr ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_ctrl_add_handler (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_5__*,int) ; 
 int /*<<< orphan*/ * v4l2_ctrl_radio_filter ; 
 int /*<<< orphan*/ * vbi_nr ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_3__*) ; 
 int /*<<< orphan*/  video_mux (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * video_nr ; 
 int video_register_device (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx231xx_register_analog_devices(struct cx231xx *dev)
{
	int ret;

	dev_info(dev->dev, "v4l2 driver version %s\n", CX231XX_VERSION);

	/* set default norm */
	dev->norm = V4L2_STD_PAL;
	dev->width = norm_maxw(dev);
	dev->height = norm_maxh(dev);
	dev->interlaced = 0;

	/* Analog specific initialization */
	dev->format = &format[0];

	/* Set the initial input */
	video_mux(dev, dev->video_input);

	call_all(dev, video, s_std, dev->norm);

	v4l2_ctrl_handler_init(&dev->ctrl_handler, 10);
	v4l2_ctrl_handler_init(&dev->radio_ctrl_handler, 5);

	if (dev->sd_cx25840) {
		v4l2_ctrl_add_handler(&dev->ctrl_handler,
				dev->sd_cx25840->ctrl_handler, NULL);
		v4l2_ctrl_add_handler(&dev->radio_ctrl_handler,
				dev->sd_cx25840->ctrl_handler,
				v4l2_ctrl_radio_filter);
	}

	if (dev->ctrl_handler.error)
		return dev->ctrl_handler.error;
	if (dev->radio_ctrl_handler.error)
		return dev->radio_ctrl_handler.error;

	/* enable vbi capturing */
	/* write code here...  */

	/* allocate and fill video video_device struct */
	cx231xx_vdev_init(dev, &dev->vdev, &cx231xx_video_template, "video");
#if defined(CONFIG_MEDIA_CONTROLLER)
	dev->video_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->vdev.entity, 1, &dev->video_pad);
	if (ret < 0)
		dev_err(dev->dev, "failed to initialize video media entity!\n");
#endif
	dev->vdev.ctrl_handler = &dev->ctrl_handler;
	/* register v4l2 video video_device */
	ret = video_register_device(&dev->vdev, VFL_TYPE_GRABBER,
				    video_nr[dev->devno]);
	if (ret) {
		dev_err(dev->dev,
			"unable to register video device (error=%i).\n",
			ret);
		return ret;
	}

	dev_info(dev->dev, "Registered video device %s [v4l2]\n",
		video_device_node_name(&dev->vdev));

	/* Initialize VBI template */
	cx231xx_vbi_template = cx231xx_video_template;
	strcpy(cx231xx_vbi_template.name, "cx231xx-vbi");

	/* Allocate and fill vbi video_device struct */
	cx231xx_vdev_init(dev, &dev->vbi_dev, &cx231xx_vbi_template, "vbi");

#if defined(CONFIG_MEDIA_CONTROLLER)
	dev->vbi_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->vbi_dev.entity, 1, &dev->vbi_pad);
	if (ret < 0)
		dev_err(dev->dev, "failed to initialize vbi media entity!\n");
#endif
	dev->vbi_dev.ctrl_handler = &dev->ctrl_handler;
	/* register v4l2 vbi video_device */
	ret = video_register_device(&dev->vbi_dev, VFL_TYPE_VBI,
				    vbi_nr[dev->devno]);
	if (ret < 0) {
		dev_err(dev->dev, "unable to register vbi device\n");
		return ret;
	}

	dev_info(dev->dev, "Registered VBI device %s\n",
		video_device_node_name(&dev->vbi_dev));

	if (cx231xx_boards[dev->model].radio.type == CX231XX_RADIO) {
		cx231xx_vdev_init(dev, &dev->radio_dev,
				&cx231xx_radio_template, "radio");
		dev->radio_dev.ctrl_handler = &dev->radio_ctrl_handler;
		ret = video_register_device(&dev->radio_dev, VFL_TYPE_RADIO,
					    radio_nr[dev->devno]);
		if (ret < 0) {
			dev_err(dev->dev,
				"can't register radio device\n");
			return ret;
		}
		dev_info(dev->dev, "Registered radio device as %s\n",
			video_device_node_name(&dev->radio_dev));
	}

	return 0;
}
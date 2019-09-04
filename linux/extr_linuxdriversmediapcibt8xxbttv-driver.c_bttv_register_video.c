#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ctrl_handler; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {size_t nr; } ;
struct bttv {TYPE_2__ radio_dev; TYPE_1__ c; int /*<<< orphan*/  radio_ctrl_handler; int /*<<< orphan*/  has_radio; TYPE_2__ vbi_dev; TYPE_2__ video_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  VFL_TYPE_VBI ; 
 int /*<<< orphan*/  bttv_unregister_video (struct bttv*) ; 
 int /*<<< orphan*/  bttv_video_template ; 
 int /*<<< orphan*/  dev_attr_card ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ no_overlay ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/ * radio_nr ; 
 int /*<<< orphan*/  radio_template ; 
 int /*<<< orphan*/ * vbi_nr ; 
 int /*<<< orphan*/  vdev_init (struct bttv*,TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_2__*) ; 
 int /*<<< orphan*/ * video_nr ; 
 scalar_t__ video_register_device (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bttv_register_video(struct bttv *btv)
{
	if (no_overlay > 0)
		pr_notice("Overlay support disabled\n");

	/* video */
	vdev_init(btv, &btv->video_dev, &bttv_video_template, "video");

	if (video_register_device(&btv->video_dev, VFL_TYPE_GRABBER,
				  video_nr[btv->c.nr]) < 0)
		goto err;
	pr_info("%d: registered device %s\n",
		btv->c.nr, video_device_node_name(&btv->video_dev));
	if (device_create_file(&btv->video_dev.dev,
				     &dev_attr_card)<0) {
		pr_err("%d: device_create_file 'card' failed\n", btv->c.nr);
		goto err;
	}

	/* vbi */
	vdev_init(btv, &btv->vbi_dev, &bttv_video_template, "vbi");

	if (video_register_device(&btv->vbi_dev, VFL_TYPE_VBI,
				  vbi_nr[btv->c.nr]) < 0)
		goto err;
	pr_info("%d: registered device %s\n",
		btv->c.nr, video_device_node_name(&btv->vbi_dev));

	if (!btv->has_radio)
		return 0;
	/* radio */
	vdev_init(btv, &btv->radio_dev, &radio_template, "radio");
	btv->radio_dev.ctrl_handler = &btv->radio_ctrl_handler;
	if (video_register_device(&btv->radio_dev, VFL_TYPE_RADIO,
				  radio_nr[btv->c.nr]) < 0)
		goto err;
	pr_info("%d: registered device %s\n",
		btv->c.nr, video_device_node_name(&btv->radio_dev));

	/* all done */
	return 0;

 err:
	bttv_unregister_video(btv);
	return -1;
}
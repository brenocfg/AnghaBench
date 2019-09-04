#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct saa7134_dev {int /*<<< orphan*/  ctl_volume; int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa7134_tvaudio_setmute (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_tvaudio_setvolume (struct saa7134_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tvnorm (struct saa7134_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tvnorms ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_mux (struct saa7134_dev*,int /*<<< orphan*/ ) ; 

int saa7134_video_init2(struct saa7134_dev *dev)
{
	/* init video hw */
	set_tvnorm(dev,&tvnorms[0]);
	video_mux(dev,0);
	v4l2_ctrl_handler_setup(&dev->ctrl_handler);
	saa7134_tvaudio_setmute(dev);
	saa7134_tvaudio_setvolume(dev,dev->ctl_volume);
	return 0;
}
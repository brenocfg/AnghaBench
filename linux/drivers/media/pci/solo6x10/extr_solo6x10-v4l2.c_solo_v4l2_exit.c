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
struct solo_dev {int /*<<< orphan*/ * vfd; int /*<<< orphan*/  disp_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

void solo_v4l2_exit(struct solo_dev *solo_dev)
{
	if (solo_dev->vfd == NULL)
		return;

	video_unregister_device(solo_dev->vfd);
	v4l2_ctrl_handler_free(&solo_dev->disp_hdl);
	solo_dev->vfd = NULL;
}
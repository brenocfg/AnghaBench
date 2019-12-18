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
struct TYPE_4__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_3__ {int nmodes; int /*<<< orphan*/ * cam_mode; } ;
struct gspca_dev {int curr_mode; TYPE_2__ vdev; TYPE_1__ cam; int /*<<< orphan*/  pixfmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gspca_set_default_mode(struct gspca_dev *gspca_dev)
{
	int i;

	i = gspca_dev->cam.nmodes - 1;	/* take the highest mode */
	gspca_dev->curr_mode = i;
	gspca_dev->pixfmt = gspca_dev->cam.cam_mode[i];

	/* does nothing if ctrl_handler == NULL */
	v4l2_ctrl_handler_setup(gspca_dev->vdev.ctrl_handler);
}
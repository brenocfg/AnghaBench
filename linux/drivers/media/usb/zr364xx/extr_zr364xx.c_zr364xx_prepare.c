#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* frame; } ;
struct zr364xx_camera {size_t method; int skip; int last_frame; int /*<<< orphan*/  ctrl_handler; TYPE_2__ buffer; scalar_t__ frame_count; scalar_t__ cur_frame; TYPE_3__* udev; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  bytes; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ cur_size; int /*<<< orphan*/  ulState; } ;

/* Variables and functions */
 int FRAMES ; 
 int /*<<< orphan*/  ZR364XX_READ_IDLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_4__** init ; 
 int send_control_msg (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zr364xx_prepare(struct zr364xx_camera *cam)
{
	int res;
	int i, j;

	for (i = 0; init[cam->method][i].size != -1; i++) {
		res = send_control_msg(cam->udev, 1, init[cam->method][i].value,
				     0, init[cam->method][i].bytes,
				     init[cam->method][i].size);
		if (res < 0) {
			dev_err(&cam->udev->dev,
				"error during open sequence: %d\n", i);
			return res;
		}
	}

	cam->skip = 2;
	cam->last_frame = -1;
	cam->cur_frame = 0;
	cam->frame_count = 0;
	for (j = 0; j < FRAMES; j++) {
		cam->buffer.frame[j].ulState = ZR364XX_READ_IDLE;
		cam->buffer.frame[j].cur_size = 0;
	}
	v4l2_ctrl_handler_setup(&cam->ctrl_handler);
	return 0;
}
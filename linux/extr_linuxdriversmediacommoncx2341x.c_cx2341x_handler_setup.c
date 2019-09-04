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
struct cx2341x_handler {int height; int width; int port; int /*<<< orphan*/  hdl; int /*<<< orphan*/  video_encoding; int /*<<< orphan*/  is_50hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_SET_FRAME_RATE ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_FRAME_SIZE ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_OUTPUT_PORT ; 
 scalar_t__ V4L2_MPEG_VIDEO_ENCODING_MPEG_1 ; 
 int cx2341x_hdl_api (struct cx2341x_handler*,int /*<<< orphan*/ ,int,int,...) ; 
 scalar_t__ v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

int cx2341x_handler_setup(struct cx2341x_handler *cxhdl)
{
	int h = cxhdl->height;
	int w = cxhdl->width;
	int err;

	err = cx2341x_hdl_api(cxhdl, CX2341X_ENC_SET_OUTPUT_PORT, 2, cxhdl->port, 0);
	if (err)
		return err;
	err = cx2341x_hdl_api(cxhdl, CX2341X_ENC_SET_FRAME_RATE, 1, cxhdl->is_50hz);
	if (err)
		return err;

	if (v4l2_ctrl_g_ctrl(cxhdl->video_encoding) == V4L2_MPEG_VIDEO_ENCODING_MPEG_1) {
		w /= 2;
		h /= 2;
	}
	err = cx2341x_hdl_api(cxhdl, CX2341X_ENC_SET_FRAME_SIZE, 2, h, w);
	if (err)
		return err;
	return v4l2_ctrl_handler_setup(&cxhdl->hdl);
}
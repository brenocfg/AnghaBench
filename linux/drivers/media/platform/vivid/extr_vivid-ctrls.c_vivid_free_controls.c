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
struct vivid_dev {int /*<<< orphan*/  ctrl_hdl_fb; int /*<<< orphan*/  ctrl_hdl_loop_cap; int /*<<< orphan*/  ctrl_hdl_sdtv_cap; int /*<<< orphan*/  ctrl_hdl_streaming; int /*<<< orphan*/  ctrl_hdl_user_aud; int /*<<< orphan*/  ctrl_hdl_user_vid; int /*<<< orphan*/  ctrl_hdl_user_gen; int /*<<< orphan*/  ctrl_hdl_sdr_cap; int /*<<< orphan*/  ctrl_hdl_radio_tx; int /*<<< orphan*/  ctrl_hdl_radio_rx; int /*<<< orphan*/  ctrl_hdl_vbi_out; int /*<<< orphan*/  ctrl_hdl_vbi_cap; int /*<<< orphan*/  ctrl_hdl_vid_out; int /*<<< orphan*/  ctrl_hdl_vid_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

void vivid_free_controls(struct vivid_dev *dev)
{
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_vid_cap);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_vid_out);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_vbi_cap);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_vbi_out);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_radio_rx);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_radio_tx);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_sdr_cap);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_user_gen);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_user_vid);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_user_aud);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_streaming);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_sdtv_cap);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_loop_cap);
	v4l2_ctrl_handler_free(&dev->ctrl_hdl_fb);
}
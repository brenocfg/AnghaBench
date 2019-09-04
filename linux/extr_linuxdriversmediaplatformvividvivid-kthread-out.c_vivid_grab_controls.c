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
struct vivid_dev {int /*<<< orphan*/  ctrl_tx_rgb_range; int /*<<< orphan*/  ctrl_tx_mode; int /*<<< orphan*/  ctrl_has_scaler_out; int /*<<< orphan*/  ctrl_has_compose_out; int /*<<< orphan*/  ctrl_has_crop_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vivid_grab_controls(struct vivid_dev *dev, bool grab)
{
	v4l2_ctrl_grab(dev->ctrl_has_crop_out, grab);
	v4l2_ctrl_grab(dev->ctrl_has_compose_out, grab);
	v4l2_ctrl_grab(dev->ctrl_has_scaler_out, grab);
	v4l2_ctrl_grab(dev->ctrl_tx_mode, grab);
	v4l2_ctrl_grab(dev->ctrl_tx_rgb_range, grab);
}
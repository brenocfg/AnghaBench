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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int vicam_control_msg (struct gspca_dev*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vicam_set_camera_power(struct gspca_dev *gspca_dev, int state)
{
	int ret;

	ret = vicam_control_msg(gspca_dev, 0x50, state, 0, NULL, 0);
	if (ret < 0)
		return ret;

	if (state)
		ret = vicam_control_msg(gspca_dev, 0x55, 1, 0, NULL, 0);

	return ret;
}
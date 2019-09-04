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
struct pwc_device {int* ctrl_buf; TYPE_4__* motor_tilt; TYPE_3__* motor_pan; TYPE_2__* motor_tilt_reset; TYPE_1__* motor_pan_reset; } ;
struct TYPE_8__ {int val; scalar_t__ is_new; } ;
struct TYPE_7__ {int val; scalar_t__ is_new; } ;
struct TYPE_6__ {scalar_t__ is_new; } ;
struct TYPE_5__ {scalar_t__ is_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_RELATIVE_CONTROL_FORMATTER ; 
 int /*<<< orphan*/  PT_RESET_CONTROL_FORMATTER ; 
 int /*<<< orphan*/  SET_MPT_CTL ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int pwc_set_motor(struct pwc_device *pdev)
{
	int ret;

	pdev->ctrl_buf[0] = 0;
	if (pdev->motor_pan_reset->is_new)
		pdev->ctrl_buf[0] |= 0x01;
	if (pdev->motor_tilt_reset->is_new)
		pdev->ctrl_buf[0] |= 0x02;
	if (pdev->motor_pan_reset->is_new || pdev->motor_tilt_reset->is_new) {
		ret = send_control_msg(pdev, SET_MPT_CTL,
				       PT_RESET_CONTROL_FORMATTER,
				       pdev->ctrl_buf, 1);
		if (ret < 0)
			return ret;
	}

	memset(pdev->ctrl_buf, 0, 4);
	if (pdev->motor_pan->is_new) {
		pdev->ctrl_buf[0] = pdev->motor_pan->val & 0xFF;
		pdev->ctrl_buf[1] = (pdev->motor_pan->val >> 8);
	}
	if (pdev->motor_tilt->is_new) {
		pdev->ctrl_buf[2] = pdev->motor_tilt->val & 0xFF;
		pdev->ctrl_buf[3] = (pdev->motor_tilt->val >> 8);
	}
	if (pdev->motor_pan->is_new || pdev->motor_tilt->is_new) {
		ret = send_control_msg(pdev, SET_MPT_CTL,
				       PT_RELATIVE_CONTROL_FORMATTER,
				       pdev->ctrl_buf, 4);
		if (ret < 0)
			return ret;
	}

	return 0;
}
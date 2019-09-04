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
struct pwc_device {int exposure_valid; TYPE_2__* exposure; TYPE_1__* exposure_auto; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; scalar_t__ is_new; } ;
struct TYPE_3__ {scalar_t__ val; scalar_t__ is_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRESET_SHUTTER_FORMATTER ; 
 int /*<<< orphan*/  SET_LUM_CTL ; 
 int /*<<< orphan*/  SHUTTER_MODE_FORMATTER ; 
 scalar_t__ V4L2_EXPOSURE_AUTO ; 
 int pwc_set_u16_ctrl (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pwc_set_u8_ctrl (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pwc_set_exposure_auto(struct pwc_device *pdev)
{
	int ret;
	int is_auto = pdev->exposure_auto->val == V4L2_EXPOSURE_AUTO;

	if (pdev->exposure_auto->is_new) {
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      SHUTTER_MODE_FORMATTER,
				      is_auto ? 0 : 0xff);
		if (ret)
			return ret;

		if (is_auto)
			pdev->exposure_valid = false; /* Force cache update */
	}

	if (is_auto)
		return 0;

	if (pdev->exposure->is_new) {
		ret = pwc_set_u16_ctrl(pdev, SET_LUM_CTL,
				       PRESET_SHUTTER_FORMATTER,
				       pdev->exposure->val);
		if (ret)
			return ret;
	}
	return 0;
}
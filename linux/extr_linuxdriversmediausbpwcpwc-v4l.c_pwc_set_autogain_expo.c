#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pwc_device {int gain_valid; int exposure_valid; TYPE_2__* exposure; TYPE_1__* gain; TYPE_3__* autogain; } ;
struct TYPE_6__ {scalar_t__ val; scalar_t__ is_new; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; scalar_t__ is_new; } ;
struct TYPE_4__ {int val; scalar_t__ is_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC_MODE_FORMATTER ; 
 int /*<<< orphan*/  PRESET_AGC_FORMATTER ; 
 int /*<<< orphan*/  PRESET_SHUTTER_FORMATTER ; 
 int /*<<< orphan*/  SET_LUM_CTL ; 
 int pwc_set_u16_ctrl (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pwc_set_u8_ctrl (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pwc_set_autogain_expo(struct pwc_device *pdev)
{
	int ret;

	if (pdev->autogain->is_new) {
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      AGC_MODE_FORMATTER,
				      pdev->autogain->val ? 0 : 0xff);
		if (ret)
			return ret;

		if (pdev->autogain->val) {
			pdev->gain_valid     = false; /* Force cache update */
			pdev->exposure_valid = false; /* Force cache update */
		}
	}

	if (pdev->autogain->val)
		return 0;

	if (pdev->gain->is_new) {
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      PRESET_AGC_FORMATTER,
				      pdev->gain->val);
		if (ret)
			return ret;
	}

	if (pdev->exposure->is_new) {
		ret = pwc_set_u16_ctrl(pdev, SET_LUM_CTL,
				       PRESET_SHUTTER_FORMATTER,
				       pdev->exposure->val);
		if (ret)
			return ret;
	}
	return 0;
}
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
struct pwc_device {int color_bal_valid; TYPE_2__* blue_balance; TYPE_1__* red_balance; TYPE_3__* auto_white_balance; } ;
struct TYPE_6__ {scalar_t__ val; scalar_t__ is_new; } ;
struct TYPE_5__ {scalar_t__ val; scalar_t__ is_new; } ;
struct TYPE_4__ {scalar_t__ val; scalar_t__ is_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRESET_MANUAL_BLUE_GAIN_FORMATTER ; 
 int /*<<< orphan*/  PRESET_MANUAL_RED_GAIN_FORMATTER ; 
 int /*<<< orphan*/  SET_CHROM_CTL ; 
 int /*<<< orphan*/  WB_MODE_FORMATTER ; 
 scalar_t__ awb_fl ; 
 scalar_t__ awb_indoor ; 
 scalar_t__ awb_manual ; 
 scalar_t__ awb_outdoor ; 
 int /*<<< orphan*/  pwc_g_volatile_ctrl (TYPE_3__*) ; 
 int pwc_set_u8_ctrl (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pwc_set_awb(struct pwc_device *pdev)
{
	int ret;

	if (pdev->auto_white_balance->is_new) {
		ret = pwc_set_u8_ctrl(pdev, SET_CHROM_CTL,
				      WB_MODE_FORMATTER,
				      pdev->auto_white_balance->val);
		if (ret)
			return ret;

		if (pdev->auto_white_balance->val != awb_manual)
			pdev->color_bal_valid = false; /* Force cache update */

		/*
		 * If this is a preset, update our red / blue balance values
		 * so that events get generated for the new preset values
		 */
		if (pdev->auto_white_balance->val == awb_indoor ||
		    pdev->auto_white_balance->val == awb_outdoor ||
		    pdev->auto_white_balance->val == awb_fl)
			pwc_g_volatile_ctrl(pdev->auto_white_balance);
	}
	if (pdev->auto_white_balance->val != awb_manual)
		return 0;

	if (pdev->red_balance->is_new) {
		ret = pwc_set_u8_ctrl(pdev, SET_CHROM_CTL,
				      PRESET_MANUAL_RED_GAIN_FORMATTER,
				      pdev->red_balance->val);
		if (ret)
			return ret;
	}

	if (pdev->blue_balance->is_new) {
		ret = pwc_set_u8_ctrl(pdev, SET_CHROM_CTL,
				      PRESET_MANUAL_BLUE_GAIN_FORMATTER,
				      pdev->blue_balance->val);
		if (ret)
			return ret;
	}
	return 0;
}
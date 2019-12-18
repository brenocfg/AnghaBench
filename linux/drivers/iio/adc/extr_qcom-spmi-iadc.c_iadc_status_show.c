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
typedef  int /*<<< orphan*/  u8 ;
struct iadc_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IADC_CH_SEL_CTL ; 
 int /*<<< orphan*/  IADC_CONV_REQ ; 
 int /*<<< orphan*/  IADC_DIG_PARAM ; 
 int /*<<< orphan*/  IADC_EN_CTL1 ; 
 int /*<<< orphan*/  IADC_MODE_CTL ; 
 int /*<<< orphan*/  IADC_STATUS1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iadc_read (struct iadc_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iadc_status_show(struct iadc_chip *iadc)
{
	u8 mode, sta1, chan, dig, en, req;
	int ret;

	ret = iadc_read(iadc, IADC_MODE_CTL, &mode);
	if (ret < 0)
		return;

	ret = iadc_read(iadc, IADC_DIG_PARAM, &dig);
	if (ret < 0)
		return;

	ret = iadc_read(iadc, IADC_CH_SEL_CTL, &chan);
	if (ret < 0)
		return;

	ret = iadc_read(iadc, IADC_CONV_REQ, &req);
	if (ret < 0)
		return;

	ret = iadc_read(iadc, IADC_STATUS1, &sta1);
	if (ret < 0)
		return;

	ret = iadc_read(iadc, IADC_EN_CTL1, &en);
	if (ret < 0)
		return;

	dev_err(iadc->dev,
		"mode:%02x en:%02x chan:%02x dig:%02x req:%02x sta1:%02x\n",
		mode, en, chan, dig, req, sta1);
}
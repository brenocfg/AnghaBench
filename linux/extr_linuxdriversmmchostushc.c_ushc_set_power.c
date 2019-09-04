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
typedef  int /*<<< orphan*/  u16 ;
struct ushc_data {int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  USHC_PWR_CTRL ; 
 int /*<<< orphan*/  USHC_PWR_CTRL_3V3 ; 
 int /*<<< orphan*/  USHC_PWR_CTRL_OFF ; 
 int /*<<< orphan*/  USHC_PWR_CTRL_TYPE ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ushc_set_power(struct ushc_data *ushc, unsigned char power_mode)
{
	u16 voltage;

	switch (power_mode) {
	case MMC_POWER_OFF:
		voltage = USHC_PWR_CTRL_OFF;
		break;
	case MMC_POWER_UP:
	case MMC_POWER_ON:
		voltage = USHC_PWR_CTRL_3V3;
		break;
	default:
		return -EINVAL;
	}

	return usb_control_msg(ushc->usb_dev, usb_sndctrlpipe(ushc->usb_dev, 0),
			       USHC_PWR_CTRL, USHC_PWR_CTRL_TYPE,
			       voltage, 0, NULL, 0, 100);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtsx_ucr {int ic_version; int is_rts5179; TYPE_1__* pusb_intf; int /*<<< orphan*/  package; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CARD_SHARE_LQFP_SEL ; 
 int /*<<< orphan*/  CARD_SHARE_MODE ; 
 int /*<<< orphan*/  CFG_MODE_1 ; 
 int /*<<< orphan*/  CLK_CHANGE ; 
 int /*<<< orphan*/  CLK_DIV ; 
 int /*<<< orphan*/  FPDCTL ; 
 int /*<<< orphan*/  HW_VERSION ; 
 int HW_VER_MASK ; 
 int /*<<< orphan*/  LQFP48 ; 
 int /*<<< orphan*/  QFN24 ; 
 int RTS5179 ; 
 int /*<<< orphan*/  SSC_POWER_MASK ; 
 int SSC_POWER_ON ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rtsx_usb_clear_fsm_err (struct rtsx_ucr*) ; 
 int rtsx_usb_read_register (struct rtsx_ucr*,int /*<<< orphan*/ ,int*) ; 
 int rtsx_usb_reset_chip (struct rtsx_ucr*) ; 
 int rtsx_usb_write_register (struct rtsx_ucr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rtsx_usb_init_chip(struct rtsx_ucr *ucr)
{
	int ret;
	u8 val;

	rtsx_usb_clear_fsm_err(ucr);

	/* power on SSC */
	ret = rtsx_usb_write_register(ucr,
			FPDCTL, SSC_POWER_MASK, SSC_POWER_ON);
	if (ret)
		return ret;

	usleep_range(100, 1000);
	ret = rtsx_usb_write_register(ucr, CLK_DIV, CLK_CHANGE, 0x00);
	if (ret)
		return ret;

	/* determine IC version */
	ret = rtsx_usb_read_register(ucr, HW_VERSION, &val);
	if (ret)
		return ret;

	ucr->ic_version = val & HW_VER_MASK;

	/* determine package */
	ret = rtsx_usb_read_register(ucr, CARD_SHARE_MODE, &val);
	if (ret)
		return ret;

	if (val & CARD_SHARE_LQFP_SEL) {
		ucr->package = LQFP48;
		dev_dbg(&ucr->pusb_intf->dev, "Package: LQFP48\n");
	} else {
		ucr->package = QFN24;
		dev_dbg(&ucr->pusb_intf->dev, "Package: QFN24\n");
	}

	/* determine IC variations */
	rtsx_usb_read_register(ucr, CFG_MODE_1, &val);
	if (val & RTS5179) {
		ucr->is_rts5179 = true;
		dev_dbg(&ucr->pusb_intf->dev, "Device is rts5179\n");
	} else {
		ucr->is_rts5179 = false;
	}

	return rtsx_usb_reset_chip(ucr);
}
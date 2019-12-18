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
struct rtsx_ucr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_PULL_CTL1 ; 
 int /*<<< orphan*/  CARD_PULL_CTL2 ; 
 int /*<<< orphan*/  CARD_PULL_CTL3 ; 
 int /*<<< orphan*/  CARD_PULL_CTL4 ; 
 int /*<<< orphan*/  CARD_PULL_CTL5 ; 
 int /*<<< orphan*/  CARD_PULL_CTL6 ; 
 int /*<<< orphan*/  MODE_C ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_usb_add_cmd (struct rtsx_ucr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_usb_init_cmd (struct rtsx_ucr*) ; 
 int rtsx_usb_send_cmd (struct rtsx_ucr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ms_pull_ctl_disable_qfn24(struct rtsx_ucr *ucr)
{
	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL1, 0xFF, 0x65);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL2, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL3, 0xFF, 0x95);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL4, 0xFF, 0x55);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL5, 0xFF, 0x56);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL6, 0xFF, 0x59);

	return rtsx_usb_send_cmd(ucr, MODE_C, 100);
}
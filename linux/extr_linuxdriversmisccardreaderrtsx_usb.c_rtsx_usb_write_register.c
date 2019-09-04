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
typedef  int /*<<< orphan*/  u16 ;
struct rtsx_ucr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_C ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_usb_add_cmd (struct rtsx_ucr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_usb_init_cmd (struct rtsx_ucr*) ; 
 int rtsx_usb_send_cmd (struct rtsx_ucr*,int /*<<< orphan*/ ,int) ; 

int rtsx_usb_write_register(struct rtsx_ucr *ucr, u16 addr, u8 mask, u8 data)
{
	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, addr, mask, data);
	return rtsx_usb_send_cmd(ucr, MODE_C, 100);
}
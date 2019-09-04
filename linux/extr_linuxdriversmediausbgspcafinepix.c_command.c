#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int member_0; int member_7; int member_8; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ u8 ;
struct gspca_dev {int /*<<< orphan*/  usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPIX_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_GET_STATUS ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int command(struct gspca_dev *gspca_dev,
		int order)	/* 0: reset, 1: frame request */
{
	static u8 order_values[2][12] = {
		{0xc6, 0, 0, 0, 0, 0, 0,    0, 0x20, 0, 0, 0},	/* reset */
		{0xd3, 0, 0, 0, 0, 0, 0, 0x01,    0, 0, 0, 0},	/* fr req */
	};

	memcpy(gspca_dev->usb_buf, order_values[order], 12);
	return usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			USB_REQ_GET_STATUS,
			USB_DIR_OUT | USB_TYPE_CLASS |
			USB_RECIP_INTERFACE, 0, 0, gspca_dev->usb_buf,
			12, FPIX_TIMEOUT);
}
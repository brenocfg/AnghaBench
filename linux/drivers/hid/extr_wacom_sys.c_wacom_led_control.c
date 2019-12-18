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
struct TYPE_8__ {unsigned char llv; unsigned char hlv; unsigned char img_lum; TYPE_3__* groups; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_1__ features; scalar_t__ pid; } ;
struct wacom {int /*<<< orphan*/  hdev; TYPE_4__ led; TYPE_2__ wacom_wac; } ;
struct TYPE_7__ {int select; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 scalar_t__ HID_GENERIC ; 
 scalar_t__ INTUOS5S ; 
 scalar_t__ INTUOSP2_BT ; 
 scalar_t__ INTUOSPL ; 
 scalar_t__ REMOTE ; 
 scalar_t__ WACOM_21UX2 ; 
 scalar_t__ WACOM_24HD ; 
 unsigned char WAC_CMD_LED_CONTROL ; 
 unsigned char WAC_CMD_LED_CONTROL_GENERIC ; 
 int /*<<< orphan*/  WAC_CMD_RETRIES ; 
 unsigned char WAC_CMD_WL_INTUOSP2 ; 
 unsigned char WAC_CMD_WL_LED_CONTROL ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_get_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int wacom_set_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wacom_led_control(struct wacom *wacom)
{
	unsigned char *buf;
	int retval;
	unsigned char report_id = WAC_CMD_LED_CONTROL;
	int buf_size = 9;

	if (!wacom->led.groups)
		return -ENOTSUPP;

	if (wacom->wacom_wac.features.type == REMOTE)
		return -ENOTSUPP;

	if (wacom->wacom_wac.pid) { /* wireless connected */
		report_id = WAC_CMD_WL_LED_CONTROL;
		buf_size = 13;
	}
	else if (wacom->wacom_wac.features.type == INTUOSP2_BT) {
		report_id = WAC_CMD_WL_INTUOSP2;
		buf_size = 51;
	}
	buf = kzalloc(buf_size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	if (wacom->wacom_wac.features.type == HID_GENERIC) {
		buf[0] = WAC_CMD_LED_CONTROL_GENERIC;
		buf[1] = wacom->led.llv;
		buf[2] = wacom->led.groups[0].select & 0x03;

	} else if ((wacom->wacom_wac.features.type >= INTUOS5S &&
	    wacom->wacom_wac.features.type <= INTUOSPL)) {
		/*
		 * Touch Ring and crop mark LED luminance may take on
		 * one of four values:
		 *    0 = Low; 1 = Medium; 2 = High; 3 = Off
		 */
		int ring_led = wacom->led.groups[0].select & 0x03;
		int ring_lum = (((wacom->led.llv & 0x60) >> 5) - 1) & 0x03;
		int crop_lum = 0;
		unsigned char led_bits = (crop_lum << 4) | (ring_lum << 2) | (ring_led);

		buf[0] = report_id;
		if (wacom->wacom_wac.pid) {
			wacom_get_report(wacom->hdev, HID_FEATURE_REPORT,
					 buf, buf_size, WAC_CMD_RETRIES);
			buf[0] = report_id;
			buf[4] = led_bits;
		} else
			buf[1] = led_bits;
	}
	else if (wacom->wacom_wac.features.type == INTUOSP2_BT) {
		buf[0] = report_id;
		buf[4] = 100; // Power Connection LED (ORANGE)
		buf[5] = 100; // BT Connection LED (BLUE)
		buf[6] = 100; // Paper Mode (RED?)
		buf[7] = 100; // Paper Mode (GREEN?)
		buf[8] = 100; // Paper Mode (BLUE?)
		buf[9] = wacom->led.llv;
		buf[10] = wacom->led.groups[0].select & 0x03;
	}
	else {
		int led = wacom->led.groups[0].select | 0x4;

		if (wacom->wacom_wac.features.type == WACOM_21UX2 ||
		    wacom->wacom_wac.features.type == WACOM_24HD)
			led |= (wacom->led.groups[1].select << 4) | 0x40;

		buf[0] = report_id;
		buf[1] = led;
		buf[2] = wacom->led.llv;
		buf[3] = wacom->led.hlv;
		buf[4] = wacom->led.img_lum;
	}

	retval = wacom_set_report(wacom->hdev, HID_FEATURE_REPORT, buf, buf_size,
				  WAC_CMD_RETRIES);
	kfree(buf);

	return retval;
}
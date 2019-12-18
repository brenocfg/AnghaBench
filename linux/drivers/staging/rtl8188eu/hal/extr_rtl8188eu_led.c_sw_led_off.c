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
typedef  int u8 ;
struct adapter {scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; } ;
struct LED_871x {int bLedOn; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  REG_LEDCFG2 ; 
 int /*<<< orphan*/  REG_MAC_PINMUX_CFG ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

void sw_led_off(struct adapter *padapter, struct LED_871x *pLed)
{
	u8 led_cfg;

	if (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		goto exit;

	led_cfg = usb_read8(padapter, REG_LEDCFG2);/* 0x4E */

	/*  Open-drain arrangement for controlling the LED) */
	led_cfg &= 0x90; /*  Set to software control. */
	usb_write8(padapter, REG_LEDCFG2, (led_cfg | BIT(3)));
	led_cfg = usb_read8(padapter, REG_MAC_PINMUX_CFG);
	led_cfg &= 0xFE;
	usb_write8(padapter, REG_MAC_PINMUX_CFG, led_cfg);
exit:
	pLed->bLedOn = false;
}
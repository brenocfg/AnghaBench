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
struct _adapter {scalar_t__ driver_stopped; scalar_t__ surprise_removed; } ;
struct LED_871x {int LedPin; int bLedOn; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEDCFG ; 
#define  LED_PIN_GPIO0 130 
#define  LED_PIN_LED0 129 
#define  LED_PIN_LED1 128 
 int r8712_read8 (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SwLedOn(struct _adapter *padapter, struct LED_871x *pLed)
{
	u8	LedCfg;

	if (padapter->surprise_removed || padapter->driver_stopped)
		return;
	LedCfg = r8712_read8(padapter, LEDCFG);
	switch (pLed->LedPin) {
	case LED_PIN_GPIO0:
		break;
	case LED_PIN_LED0:
		/* SW control led0 on.*/
		r8712_write8(padapter, LEDCFG, LedCfg & 0xf0);
		break;
	case LED_PIN_LED1:
		/* SW control led1 on.*/
		r8712_write8(padapter, LEDCFG, LedCfg & 0x0f);
		break;
	default:
		break;
	}
	pLed->bLedOn = true;
}
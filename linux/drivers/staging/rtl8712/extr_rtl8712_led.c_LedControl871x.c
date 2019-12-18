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
struct led_priv {int LedStrategy; int /*<<< orphan*/  bRegUseLed; } ;
struct _adapter {struct led_priv ledpriv; } ;
typedef  enum LED_CTL_MODE { ____Placeholder_LED_CTL_MODE } LED_CTL_MODE ;

/* Variables and functions */
#define  SW_LED_MODE0 134 
#define  SW_LED_MODE1 133 
#define  SW_LED_MODE2 132 
#define  SW_LED_MODE3 131 
#define  SW_LED_MODE4 130 
#define  SW_LED_MODE5 129 
#define  SW_LED_MODE6 128 
 int /*<<< orphan*/  SwLedControlMode1 (struct _adapter*,int) ; 
 int /*<<< orphan*/  SwLedControlMode2 (struct _adapter*,int) ; 
 int /*<<< orphan*/  SwLedControlMode3 (struct _adapter*,int) ; 
 int /*<<< orphan*/  SwLedControlMode4 (struct _adapter*,int) ; 
 int /*<<< orphan*/  SwLedControlMode5 (struct _adapter*,int) ; 
 int /*<<< orphan*/  SwLedControlMode6 (struct _adapter*,int) ; 

void LedControl871x(struct _adapter *padapter, enum LED_CTL_MODE LedAction)
{
	struct led_priv	*ledpriv = &padapter->ledpriv;

	if (!ledpriv->bRegUseLed)
		return;
	switch (ledpriv->LedStrategy) {
	case SW_LED_MODE0:
		break;
	case SW_LED_MODE1:
		SwLedControlMode1(padapter, LedAction);
		break;
	case SW_LED_MODE2:
		SwLedControlMode2(padapter, LedAction);
		break;
	case SW_LED_MODE3:
		SwLedControlMode3(padapter, LedAction);
		break;
	case SW_LED_MODE4:
		SwLedControlMode4(padapter, LedAction);
		break;
	case SW_LED_MODE5:
		SwLedControlMode5(padapter, LedAction);
		break;
	case SW_LED_MODE6:
		SwLedControlMode6(padapter, LedAction);
		break;
	default:
		break;
	}
}
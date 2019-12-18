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
struct led_priv {int /*<<< orphan*/  SwLed1; int /*<<< orphan*/  SwLed0; } ;
struct _adapter {struct led_priv ledpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeInitLed871x (int /*<<< orphan*/ *) ; 

void r8712_DeInitSwLeds(struct _adapter *padapter)
{
	struct led_priv	*ledpriv = &padapter->ledpriv;

	DeInitLed871x(&ledpriv->SwLed0);
	DeInitLed871x(&ledpriv->SwLed1);
}
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
typedef  int u16 ;
struct wm97xx {int* dig; TYPE_1__* mach_ops; int /*<<< orphan*/  acc_rate; int /*<<< orphan*/  acc_slot; } ;
struct TYPE_2__ {int (* acc_startup ) (struct wm97xx*) ;int /*<<< orphan*/  (* acc_shutdown ) (struct wm97xx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_WM9713_DIG1 ; 
 int /*<<< orphan*/  AC97_WM9713_DIG2 ; 
 int /*<<< orphan*/  AC97_WM9713_DIG3 ; 
 int WM9713_ADCSEL_MASK ; 
 int WM9713_ADCSEL_PRES ; 
 int WM9713_ADCSEL_X ; 
 int WM9713_ADCSEL_Y ; 
 int WM9713_COO ; 
 int WM9713_CTC ; 
 int WM9713_PDEN ; 
 int WM97XX_CM_RATE_MASK ; 
 int WM97XX_DELAY (int /*<<< orphan*/ ) ; 
 int WM97XX_DELAY_MASK ; 
 int WM97XX_RATE (int /*<<< orphan*/ ) ; 
 int WM97XX_SLEN ; 
 int WM97XX_SLT (int /*<<< orphan*/ ) ; 
 int WM97XX_SLT_MASK ; 
 int /*<<< orphan*/  delay ; 
 scalar_t__ pil ; 
 int stub1 (struct wm97xx*) ; 
 int /*<<< orphan*/  stub2 (struct wm97xx*) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm9713_acc_enable(struct wm97xx *wm, int enable)
{
	u16 dig1, dig2, dig3;
	int ret = 0;

	dig1 = wm->dig[0];
	dig2 = wm->dig[1];
	dig3 = wm->dig[2];

	if (enable) {
		/* continuous mode */
		if (wm->mach_ops->acc_startup &&
			(ret = wm->mach_ops->acc_startup(wm)) < 0)
			return ret;

		dig1 &= ~WM9713_ADCSEL_MASK;
		dig1 |= WM9713_CTC | WM9713_COO | WM9713_ADCSEL_X |
			WM9713_ADCSEL_Y;
		if (pil)
			dig1 |= WM9713_ADCSEL_PRES;
		dig2 &= ~(WM97XX_DELAY_MASK | WM97XX_SLT_MASK  |
			WM97XX_CM_RATE_MASK);
		dig2 |= WM97XX_SLEN | WM97XX_DELAY(delay) |
		WM97XX_SLT(wm->acc_slot) | WM97XX_RATE(wm->acc_rate);
		dig3 |= WM9713_PDEN;
	} else {
		dig1 &= ~(WM9713_CTC | WM9713_COO);
		dig2 &= ~WM97XX_SLEN;
		dig3 &= ~WM9713_PDEN;
		if (wm->mach_ops->acc_shutdown)
			wm->mach_ops->acc_shutdown(wm);
	}

	wm97xx_reg_write(wm, AC97_WM9713_DIG1, dig1);
	wm97xx_reg_write(wm, AC97_WM9713_DIG2, dig2);
	wm97xx_reg_write(wm, AC97_WM9713_DIG3, dig3);

	return ret;
}
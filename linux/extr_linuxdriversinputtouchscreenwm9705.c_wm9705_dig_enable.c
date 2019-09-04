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
struct wm97xx {int* dig; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_WM97XX_DIGITISER2 ; 
 int /*<<< orphan*/  AC97_WM97XX_DIGITISER_RD ; 
 int WM97XX_PRP_DET_DIG ; 
 int /*<<< orphan*/  wm97xx_reg_read (struct wm97xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wm9705_dig_enable(struct wm97xx *wm, int enable)
{
	if (enable) {
		wm97xx_reg_write(wm, AC97_WM97XX_DIGITISER2,
				 wm->dig[2] | WM97XX_PRP_DET_DIG);
		wm97xx_reg_read(wm, AC97_WM97XX_DIGITISER_RD); /* dummy read */
	} else
		wm97xx_reg_write(wm, AC97_WM97XX_DIGITISER2,
				 wm->dig[2] & ~WM97XX_PRP_DET_DIG);
}
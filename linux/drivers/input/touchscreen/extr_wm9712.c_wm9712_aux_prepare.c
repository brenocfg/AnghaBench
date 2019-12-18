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
struct wm97xx {int /*<<< orphan*/  dig; int /*<<< orphan*/  dig_save; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_WM97XX_DIGITISER1 ; 
 int /*<<< orphan*/  AC97_WM97XX_DIGITISER2 ; 
 int /*<<< orphan*/  WM97XX_PRP_DET_DIG ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm9712_aux_prepare(struct wm97xx *wm)
{
	memcpy(wm->dig_save, wm->dig, sizeof(wm->dig));
	wm97xx_reg_write(wm, AC97_WM97XX_DIGITISER1, 0);
	wm97xx_reg_write(wm, AC97_WM97XX_DIGITISER2, WM97XX_PRP_DET_DIG);
}
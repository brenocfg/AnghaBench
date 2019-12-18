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
struct wm97xx {int /*<<< orphan*/ * dig_save; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_WM9713_DIG1 ; 
 int /*<<< orphan*/  AC97_WM9713_DIG2 ; 
 int /*<<< orphan*/  AC97_WM9713_DIG3 ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm9713_dig_restore(struct wm97xx *wm)
{
	wm97xx_reg_write(wm, AC97_WM9713_DIG1, wm->dig_save[0]);
	wm97xx_reg_write(wm, AC97_WM9713_DIG2, wm->dig_save[1]);
	wm97xx_reg_write(wm, AC97_WM9713_DIG3, wm->dig_save[2]);
}
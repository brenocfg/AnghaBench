#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wm97xx {int* dig; int* gpio; int misc; TYPE_3__* ac97; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write ) (TYPE_3__*,int,int) ;} ;

/* Variables and functions */
 int AC97_GPIO_CFG ; 
 int AC97_MISC_AFE ; 
 int AC97_WM9713_DIG1 ; 
 int AC97_WM9713_DIG3 ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,int) ; 

void wm97xx_reg_write(struct wm97xx *wm, u16 reg, u16 val)
{
	/* cache digitiser registers */
	if (reg >= AC97_WM9713_DIG1 && reg <= AC97_WM9713_DIG3)
		wm->dig[(reg - AC97_WM9713_DIG1) >> 1] = val;

	/* cache gpio regs */
	if (reg >= AC97_GPIO_CFG && reg <= AC97_MISC_AFE)
		wm->gpio[(reg - AC97_GPIO_CFG) >> 1] = val;

	/* wm9713 irq reg */
	if (reg == 0x5a)
		wm->misc = val;

	if (wm->ac97)
		wm->ac97->bus->ops->write(wm->ac97, reg, val);
}
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
struct a21_wdt_drv {int /*<<< orphan*/ * gpios; } ;

/* Variables and functions */
 size_t GPIO_WD_RST0 ; 
 size_t GPIO_WD_RST1 ; 
 size_t GPIO_WD_RST2 ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int a21_wdt_get_bootstatus(struct a21_wdt_drv *drv)
{
	int reset = 0;

	reset |= gpiod_get_value(drv->gpios[GPIO_WD_RST0]) ? (1 << 0) : 0;
	reset |= gpiod_get_value(drv->gpios[GPIO_WD_RST1]) ? (1 << 1) : 0;
	reset |= gpiod_get_value(drv->gpios[GPIO_WD_RST2]) ? (1 << 2) : 0;

	return reset;
}
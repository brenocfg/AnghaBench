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
struct usb_phy_generic {int /*<<< orphan*/  gpiod_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void nop_reset(struct usb_phy_generic *nop)
{
	if (!nop->gpiod_reset)
		return;

	gpiod_set_value_cansleep(nop->gpiod_reset, 1);
	usleep_range(10000, 20000);
	gpiod_set_value_cansleep(nop->gpiod_reset, 0);
}
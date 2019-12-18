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
struct rcar_gen3_usb3 {scalar_t__ base; scalar_t__ ssc_range; } ;

/* Variables and functions */
 int CLKSET0_PRIVATE ; 
 int CLKSET0_USB30_FSEL_USB_EXTAL ; 
 int PHY_ENABLE_RESET_EN ; 
 scalar_t__ USB30_CLKSET0 ; 
 scalar_t__ USB30_PHY_ENABLE ; 
 int /*<<< orphan*/  rcar_gen3_phy_usb3_enable_ssc (struct rcar_gen3_usb3*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  write_clkset1_for_usb_extal (struct rcar_gen3_usb3*,int) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void rcar_gen3_phy_usb3_select_usb_extal(struct rcar_gen3_usb3 *r)
{
	write_clkset1_for_usb_extal(r, false);
	if (r->ssc_range)
		rcar_gen3_phy_usb3_enable_ssc(r);
	writew(CLKSET0_PRIVATE | CLKSET0_USB30_FSEL_USB_EXTAL,
	       r->base + USB30_CLKSET0);
	writew(PHY_ENABLE_RESET_EN, r->base + USB30_PHY_ENABLE);
	write_clkset1_for_usb_extal(r, true);
	usleep_range(10, 20);
	write_clkset1_for_usb_extal(r, false);
}
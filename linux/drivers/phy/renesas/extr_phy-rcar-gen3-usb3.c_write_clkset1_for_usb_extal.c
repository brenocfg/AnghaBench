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
typedef  int u16 ;
struct rcar_gen3_usb3 {scalar_t__ base; } ;

/* Variables and functions */
 int CLKSET1_PHYRESET ; 
 int CLKSET1_PRIVATE_2_1 ; 
 int CLKSET1_REF_CLKDIV ; 
 int CLKSET1_USB30_PLL_MULTI_USB_EXTAL ; 
 scalar_t__ USB30_CLKSET1 ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void write_clkset1_for_usb_extal(struct rcar_gen3_usb3 *r, bool reset)
{
	u16 val = CLKSET1_USB30_PLL_MULTI_USB_EXTAL |
		  CLKSET1_REF_CLKDIV | CLKSET1_PRIVATE_2_1;

	if (reset)
		val |= CLKSET1_PHYRESET;

	writew(val, r->base + USB30_CLKSET1);
}
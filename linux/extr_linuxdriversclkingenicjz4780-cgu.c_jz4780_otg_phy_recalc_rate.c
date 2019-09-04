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
typedef  unsigned int u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ CGU_REG_USBPCR1 ; 
#define  USBPCR1_REFCLKDIV_12 131 
#define  USBPCR1_REFCLKDIV_19_2 130 
#define  USBPCR1_REFCLKDIV_24 129 
#define  USBPCR1_REFCLKDIV_48 128 
 unsigned int USBPCR1_REFCLKDIV_MASK ; 
 TYPE_1__* cgu ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static unsigned long jz4780_otg_phy_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	u32 usbpcr1;
	unsigned refclk_div;

	usbpcr1 = readl(cgu->base + CGU_REG_USBPCR1);
	refclk_div = usbpcr1 & USBPCR1_REFCLKDIV_MASK;

	switch (refclk_div) {
	case USBPCR1_REFCLKDIV_12:
		return 12000000;

	case USBPCR1_REFCLKDIV_24:
		return 24000000;

	case USBPCR1_REFCLKDIV_48:
		return 48000000;

	case USBPCR1_REFCLKDIV_19_2:
		return 19200000;
	}

	BUG();
	return parent_rate;
}
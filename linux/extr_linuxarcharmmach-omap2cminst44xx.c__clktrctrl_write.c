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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int OMAP4430_CLKTRCTRL_MASK ; 
 int OMAP4430_CLKTRCTRL_SHIFT ; 
 scalar_t__ OMAP4_CM_CLKSTCTRL ; 
 int omap4_cminst_read_inst_reg (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  omap4_cminst_write_inst_reg (int,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void _clktrctrl_write(u8 c, u8 part, u16 inst, u16 cdoffs)
{
	u32 v;

	v = omap4_cminst_read_inst_reg(part, inst, cdoffs + OMAP4_CM_CLKSTCTRL);
	v &= ~OMAP4430_CLKTRCTRL_MASK;
	v |= c << OMAP4430_CLKTRCTRL_SHIFT;
	omap4_cminst_write_inst_reg(v, part, inst, cdoffs + OMAP4_CM_CLKSTCTRL);
}
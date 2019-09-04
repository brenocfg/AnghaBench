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
typedef  int u32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_CM_CLKSTCTRL ; 
 int OMAP34XX_CLKSTCTRL_ENABLE_AUTO ; 
 int __ffs (int) ; 
 int omap2_cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool omap3xxx_cm_is_clkdm_in_hwsup(s16 module, u32 mask)
{
	u32 v;

	v = omap2_cm_read_mod_reg(module, OMAP2_CM_CLKSTCTRL);
	v &= mask;
	v >>= __ffs(mask);

	return (v == OMAP34XX_CLKSTCTRL_ENABLE_AUTO) ? 1 : 0;
}
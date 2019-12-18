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
struct pic32_wdt {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ WDTCON_REG ; 
 int WDTCON_RMCS_MASK ; 
 int WDTCON_RMCS_SHIFT ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline u32 pic32_wdt_get_clk_id(struct pic32_wdt *wdt)
{
	u32 v = readl(wdt->regs + WDTCON_REG);

	return (v >> WDTCON_RMCS_SHIFT) & WDTCON_RMCS_MASK;
}
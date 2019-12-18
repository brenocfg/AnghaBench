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

/* Variables and functions */
 int CRVML_LVDS_ON ; 
 int CRVML_PANEL_ON ; 
 int CRVML_PANEL_PORT ; 
 int HZ ; 
 int gpio_bar ; 
 int inl (int) ; 
 int /*<<< orphan*/  outl (int,int) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 

__attribute__((used)) static void cr_panel_off(void)
{
	u32 addr = gpio_bar + CRVML_PANEL_PORT;
	u32 cur = inl(addr);

	/* Power down LVDS controller first to avoid high currents */
	if (cur & CRVML_LVDS_ON) {
		cur &= ~CRVML_LVDS_ON;
		outl(cur, addr);
	}
	if (cur & CRVML_PANEL_ON) {
		schedule_timeout(HZ / 10);
		outl(cur & ~CRVML_PANEL_ON, addr);
	}
}
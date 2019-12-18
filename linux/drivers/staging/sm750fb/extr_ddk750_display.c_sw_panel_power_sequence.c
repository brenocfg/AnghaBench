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

/* Variables and functions */
 int /*<<< orphan*/  PANEL_DISPLAY_CTRL ; 
 unsigned int PANEL_DISPLAY_CTRL_DATA ; 
 unsigned int PANEL_DISPLAY_CTRL_FPEN ; 
 unsigned int PANEL_DISPLAY_CTRL_VBIASEN ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  primary_wait_vertical_sync (int) ; 

__attribute__((used)) static void sw_panel_power_sequence(int disp, int delay)
{
	unsigned int reg;

	/* disp should be 1 to open sequence */
	reg = peek32(PANEL_DISPLAY_CTRL);
	reg |= (disp ? PANEL_DISPLAY_CTRL_FPEN : 0);
	poke32(PANEL_DISPLAY_CTRL, reg);
	primary_wait_vertical_sync(delay);

	reg = peek32(PANEL_DISPLAY_CTRL);
	reg |= (disp ? PANEL_DISPLAY_CTRL_DATA : 0);
	poke32(PANEL_DISPLAY_CTRL, reg);
	primary_wait_vertical_sync(delay);

	reg = peek32(PANEL_DISPLAY_CTRL);
	reg |= (disp ? PANEL_DISPLAY_CTRL_VBIASEN : 0);
	poke32(PANEL_DISPLAY_CTRL, reg);
	primary_wait_vertical_sync(delay);

	reg = peek32(PANEL_DISPLAY_CTRL);
	reg |= (disp ? PANEL_DISPLAY_CTRL_FPEN : 0);
	poke32(PANEL_DISPLAY_CTRL, reg);
	primary_wait_vertical_sync(delay);
}
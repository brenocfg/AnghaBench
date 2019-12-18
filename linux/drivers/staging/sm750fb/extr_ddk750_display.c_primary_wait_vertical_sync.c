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
 unsigned int DISPLAY_CTRL_TIMING ; 
 int /*<<< orphan*/  PANEL_DISPLAY_CTRL ; 
 int /*<<< orphan*/  PANEL_PLL_CTRL ; 
 unsigned int PLL_CTRL_POWER ; 
 int /*<<< orphan*/  SYSTEM_CTRL ; 
 unsigned int SYSTEM_CTRL_PANEL_VSYNC_ACTIVE ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void primary_wait_vertical_sync(int delay)
{
	unsigned int status;

	/*
	 * Do not wait when the Primary PLL is off or display control is
	 * already off. This will prevent the software to wait forever.
	 */
	if (!(peek32(PANEL_PLL_CTRL) & PLL_CTRL_POWER) ||
	    !(peek32(PANEL_DISPLAY_CTRL) & DISPLAY_CTRL_TIMING))
		return;

	while (delay-- > 0) {
		/* Wait for end of vsync. */
		do {
			status = peek32(SYSTEM_CTRL);
		} while (status & SYSTEM_CTRL_PANEL_VSYNC_ACTIVE);

		/* Wait for start of vsync. */
		do {
			status = peek32(SYSTEM_CTRL);
		} while (!(status & SYSTEM_CTRL_PANEL_VSYNC_ACTIVE));
	}
}
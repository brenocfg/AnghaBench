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
struct wuxga_nt_panel {int /*<<< orphan*/  dsi; } ;

/* Variables and functions */
 int mipi_dsi_turn_on_peripheral (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wuxga_nt_panel_on(struct wuxga_nt_panel *wuxga_nt)
{
	return mipi_dsi_turn_on_peripheral(wuxga_nt->dsi);
}
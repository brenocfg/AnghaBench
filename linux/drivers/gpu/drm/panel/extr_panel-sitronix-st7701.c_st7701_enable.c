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
struct st7701 {int /*<<< orphan*/  backlight; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_ON ; 
 int /*<<< orphan*/  ST7701_DSI (struct st7701*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  backlight_enable (int /*<<< orphan*/ ) ; 
 struct st7701* panel_to_st7701 (struct drm_panel*) ; 

__attribute__((used)) static int st7701_enable(struct drm_panel *panel)
{
	struct st7701 *st7701 = panel_to_st7701(panel);

	ST7701_DSI(st7701, MIPI_DCS_SET_DISPLAY_ON, 0x00);
	backlight_enable(st7701->backlight);

	return 0;
}
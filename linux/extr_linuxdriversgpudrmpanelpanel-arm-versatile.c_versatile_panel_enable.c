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
struct versatile_panel {scalar_t__ ib2_map; int /*<<< orphan*/  dev; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB2_CTRL ; 
 int /*<<< orphan*/  IB2_CTRL_LCD_BL_ON ; 
 int /*<<< orphan*/  IB2_CTRL_LCD_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct versatile_panel* to_versatile_panel (struct drm_panel*) ; 

__attribute__((used)) static int versatile_panel_enable(struct drm_panel *panel)
{
	struct versatile_panel *vpanel = to_versatile_panel(panel);

	/* If we're on an IB2 daughterboard, turn on display */
	if (vpanel->ib2_map) {
		dev_dbg(vpanel->dev, "enable IB2 display\n");
		regmap_update_bits(vpanel->ib2_map,
				   IB2_CTRL,
				   IB2_CTRL_LCD_MASK,
				   IB2_CTRL_LCD_BL_ON);
	}

	return 0;
}
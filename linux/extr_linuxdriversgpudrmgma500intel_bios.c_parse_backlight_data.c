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
typedef  int u8 ;
struct drm_psb_private {struct bdb_lvds_backlight* lvds_bl; TYPE_1__* dev; } ;
struct bdb_lvds_options {int panel_type; } ;
struct bdb_lvds_backlight {int dummy; } ;
struct bdb_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_LVDS_BACKLIGHT ; 
 int /*<<< orphan*/  BDB_LVDS_OPTIONS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* find_section (struct bdb_header*,int /*<<< orphan*/ ) ; 
 struct bdb_lvds_backlight* kmemdup (struct bdb_lvds_backlight*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_backlight_data(struct drm_psb_private *dev_priv,
				struct bdb_header *bdb)
{
	struct bdb_lvds_backlight *vbt_lvds_bl = NULL;
	struct bdb_lvds_backlight *lvds_bl;
	u8 p_type = 0;
	void *bl_start = NULL;
	struct bdb_lvds_options *lvds_opts
				= find_section(bdb, BDB_LVDS_OPTIONS);

	dev_priv->lvds_bl = NULL;

	if (lvds_opts)
		p_type = lvds_opts->panel_type;
	else
		return;

	bl_start = find_section(bdb, BDB_LVDS_BACKLIGHT);
	vbt_lvds_bl = (struct bdb_lvds_backlight *)(bl_start + 1) + p_type;

	lvds_bl = kmemdup(vbt_lvds_bl, sizeof(*vbt_lvds_bl), GFP_KERNEL);
	if (!lvds_bl) {
		dev_err(dev_priv->dev->dev, "out of memory for backlight data\n");
		return;
	}
	dev_priv->lvds_bl = lvds_bl;
}
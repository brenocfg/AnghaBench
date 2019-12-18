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
struct lvds_dvo_timing {int dummy; } ;
struct drm_psb_private {struct drm_display_mode* sdvo_lvds_vbt_mode; } ;
struct drm_display_mode {int dummy; } ;
struct bdb_sdvo_lvds_options {int panel_type; } ;
struct bdb_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_SDVO_LVDS_OPTIONS ; 
 int /*<<< orphan*/  BDB_SDVO_PANEL_DTDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fill_detail_timing_data (struct drm_display_mode*,struct lvds_dvo_timing*) ; 
 void* find_section (struct bdb_header*,int /*<<< orphan*/ ) ; 
 struct drm_display_mode* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_sdvo_panel_data(struct drm_psb_private *dev_priv,
		      struct bdb_header *bdb)
{
	struct bdb_sdvo_lvds_options *sdvo_lvds_options;
	struct lvds_dvo_timing *dvo_timing;
	struct drm_display_mode *panel_fixed_mode;

	dev_priv->sdvo_lvds_vbt_mode = NULL;

	sdvo_lvds_options = find_section(bdb, BDB_SDVO_LVDS_OPTIONS);
	if (!sdvo_lvds_options)
		return;

	dvo_timing = find_section(bdb, BDB_SDVO_PANEL_DTDS);
	if (!dvo_timing)
		return;

	panel_fixed_mode = kzalloc(sizeof(*panel_fixed_mode), GFP_KERNEL);

	if (!panel_fixed_mode)
		return;

	fill_detail_timing_data(panel_fixed_mode,
			dvo_timing + sdvo_lvds_options->panel_type);

	dev_priv->sdvo_lvds_vbt_mode = panel_fixed_mode;

	return;
}
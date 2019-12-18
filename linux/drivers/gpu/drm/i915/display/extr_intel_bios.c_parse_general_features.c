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
struct TYPE_2__ {int /*<<< orphan*/  fdi_rx_polarity_inverted; int /*<<< orphan*/  display_clock_mode; int /*<<< orphan*/  lvds_ssc_freq; int /*<<< orphan*/  lvds_use_ssc; int /*<<< orphan*/  int_crt_support; int /*<<< orphan*/  int_tv_support; int /*<<< orphan*/  orientation; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct bdb_header {int version; } ;
struct bdb_general_features {scalar_t__ rotate_180; int /*<<< orphan*/  fdi_rx_polarity_inverted; int /*<<< orphan*/  display_clock_mode; int /*<<< orphan*/  ssc_freq; int /*<<< orphan*/  enable_ssc; int /*<<< orphan*/  int_crt_support; int /*<<< orphan*/  int_tv_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_GENERAL_FEATURES ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP ; 
 int /*<<< orphan*/  DRM_MODE_PANEL_ORIENTATION_NORMAL ; 
 int /*<<< orphan*/  DRM_MODE_PANEL_ORIENTATION_UNKNOWN ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 struct bdb_general_features* find_section (struct bdb_header const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_bios_ssc_frequency (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_general_features(struct drm_i915_private *dev_priv,
		       const struct bdb_header *bdb)
{
	const struct bdb_general_features *general;

	general = find_section(bdb, BDB_GENERAL_FEATURES);
	if (!general)
		return;

	dev_priv->vbt.int_tv_support = general->int_tv_support;
	/* int_crt_support can't be trusted on earlier platforms */
	if (bdb->version >= 155 &&
	    (HAS_DDI(dev_priv) || IS_VALLEYVIEW(dev_priv)))
		dev_priv->vbt.int_crt_support = general->int_crt_support;
	dev_priv->vbt.lvds_use_ssc = general->enable_ssc;
	dev_priv->vbt.lvds_ssc_freq =
		intel_bios_ssc_frequency(dev_priv, general->ssc_freq);
	dev_priv->vbt.display_clock_mode = general->display_clock_mode;
	dev_priv->vbt.fdi_rx_polarity_inverted = general->fdi_rx_polarity_inverted;
	if (bdb->version >= 181) {
		dev_priv->vbt.orientation = general->rotate_180 ?
			DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP :
			DRM_MODE_PANEL_ORIENTATION_NORMAL;
	} else {
		dev_priv->vbt.orientation = DRM_MODE_PANEL_ORIENTATION_UNKNOWN;
	}
	DRM_DEBUG_KMS("BDB_GENERAL_FEATURES int_tv_support %d int_crt_support %d lvds_use_ssc %d lvds_ssc_freq %d display_clock_mode %d fdi_rx_polarity_inverted %d\n",
		      dev_priv->vbt.int_tv_support,
		      dev_priv->vbt.int_crt_support,
		      dev_priv->vbt.lvds_use_ssc,
		      dev_priv->vbt.lvds_ssc_freq,
		      dev_priv->vbt.display_clock_mode,
		      dev_priv->vbt.fdi_rx_polarity_inverted);
}
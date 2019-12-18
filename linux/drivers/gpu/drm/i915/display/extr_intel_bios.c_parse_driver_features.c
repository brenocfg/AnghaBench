#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  enable; } ;
struct TYPE_4__ {TYPE_1__ psr; int /*<<< orphan*/  drrs_type; scalar_t__ int_lvds_support; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct bdb_header {int version; } ;
struct bdb_driver_features {scalar_t__ lvds_config; int /*<<< orphan*/  psr_enabled; int /*<<< orphan*/  drrs_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_DRIVER_FEATURES ; 
 scalar_t__ BDB_DRIVER_FEATURE_INT_LVDS ; 
 scalar_t__ BDB_DRIVER_FEATURE_INT_SDVO_LVDS ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRRS_NOT_SUPPORTED ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 struct bdb_driver_features* find_section (struct bdb_header const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_driver_features(struct drm_i915_private *dev_priv,
		      const struct bdb_header *bdb)
{
	const struct bdb_driver_features *driver;

	driver = find_section(bdb, BDB_DRIVER_FEATURES);
	if (!driver)
		return;

	if (INTEL_GEN(dev_priv) >= 5) {
		/*
		 * Note that we consider BDB_DRIVER_FEATURE_INT_SDVO_LVDS
		 * to mean "eDP". The VBT spec doesn't agree with that
		 * interpretation, but real world VBTs seem to.
		 */
		if (driver->lvds_config != BDB_DRIVER_FEATURE_INT_LVDS)
			dev_priv->vbt.int_lvds_support = 0;
	} else {
		/*
		 * FIXME it's not clear which BDB version has the LVDS config
		 * bits defined. Revision history in the VBT spec says:
		 * "0.92 | Add two definitions for VBT value of LVDS Active
		 *  Config (00b and 11b values defined) | 06/13/2005"
		 * but does not the specify the BDB version.
		 *
		 * So far version 134 (on i945gm) is the oldest VBT observed
		 * in the wild with the bits correctly populated. Version
		 * 108 (on i85x) does not have the bits correctly populated.
		 */
		if (bdb->version >= 134 &&
		    driver->lvds_config != BDB_DRIVER_FEATURE_INT_LVDS &&
		    driver->lvds_config != BDB_DRIVER_FEATURE_INT_SDVO_LVDS)
			dev_priv->vbt.int_lvds_support = 0;
	}

	DRM_DEBUG_KMS("DRRS State Enabled:%d\n", driver->drrs_enabled);
	/*
	 * If DRRS is not supported, drrs_type has to be set to 0.
	 * This is because, VBT is configured in such a way that
	 * static DRRS is 0 and DRRS not supported is represented by
	 * driver->drrs_enabled=false
	 */
	if (!driver->drrs_enabled)
		dev_priv->vbt.drrs_type = DRRS_NOT_SUPPORTED;
	dev_priv->vbt.psr.enable = driver->psr_enabled;
}
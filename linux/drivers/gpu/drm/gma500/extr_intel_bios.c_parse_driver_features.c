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
struct TYPE_2__ {int support; } ;
struct drm_psb_private {int lvds_enabled_in_vbt; int dplla_96mhz; TYPE_1__ edp; } ;
struct bdb_header {int dummy; } ;
struct bdb_driver_features {scalar_t__ lvds_config; scalar_t__ primary_lfp_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_DRIVER_FEATURES ; 
 scalar_t__ BDB_DRIVER_FEATURE_EDP ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__) ; 
 struct bdb_driver_features* find_section (struct bdb_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_driver_features(struct drm_psb_private *dev_priv,
		      struct bdb_header *bdb)
{
	struct bdb_driver_features *driver;

	driver = find_section(bdb, BDB_DRIVER_FEATURES);
	if (!driver)
		return;

	if (driver->lvds_config == BDB_DRIVER_FEATURE_EDP)
		dev_priv->edp.support = 1;

	dev_priv->lvds_enabled_in_vbt = driver->lvds_config != 0;
	DRM_DEBUG_KMS("LVDS VBT config bits: 0x%x\n", driver->lvds_config);

	/* This bit means to use 96Mhz for DPLL_A or not */
	if (driver->primary_lfp_id)
		dev_priv->dplla_96mhz = true;
	else
		dev_priv->dplla_96mhz = false;
}
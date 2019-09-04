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
struct drm_psb_private {int int_tv_support; int int_crt_support; int lvds_ssc_freq; int /*<<< orphan*/  lvds_use_ssc; } ;
struct bdb_header {int dummy; } ;
struct bdb_general_features {int int_tv_support; int int_crt_support; scalar_t__ ssc_freq; int /*<<< orphan*/  enable_ssc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_GENERAL_FEATURES ; 
 struct bdb_general_features* find_section (struct bdb_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_general_features(struct drm_psb_private *dev_priv,
		       struct bdb_header *bdb)
{
	struct bdb_general_features *general;

	/* Set sensible defaults in case we can't find the general block */
	dev_priv->int_tv_support = 1;
	dev_priv->int_crt_support = 1;

	general = find_section(bdb, BDB_GENERAL_FEATURES);
	if (general) {
		dev_priv->int_tv_support = general->int_tv_support;
		dev_priv->int_crt_support = general->int_crt_support;
		dev_priv->lvds_use_ssc = general->enable_ssc;

		if (dev_priv->lvds_use_ssc) {
			dev_priv->lvds_ssc_freq
				= general->ssc_freq ? 100 : 96;
		}
	}
}
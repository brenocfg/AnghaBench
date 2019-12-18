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
struct hibmc_drm_private {int mode_config_initialized; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_config_cleanup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hibmc_kms_fini(struct hibmc_drm_private *priv)
{
	if (priv->mode_config_initialized) {
		drm_mode_config_cleanup(priv->dev);
		priv->mode_config_initialized = false;
	}
}
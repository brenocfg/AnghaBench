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
struct omap_drm_private {int /*<<< orphan*/  dss; } ;

/* Variables and functions */
 int /*<<< orphan*/  dss_install_mgr_ops (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct omap_drm_private*) ; 
 int /*<<< orphan*/  mgr_ops ; 

void omap_crtc_pre_init(struct omap_drm_private *priv)
{
	dss_install_mgr_ops(priv->dss, &mgr_ops, priv);
}
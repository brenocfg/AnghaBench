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
struct omap_drm_private {int dummy; } ;
struct dss_mgr_ops {int dummy; } ;
struct dss_device {struct omap_drm_private* mgr_ops_priv; struct dss_mgr_ops const* mgr_ops; } ;

/* Variables and functions */
 int EBUSY ; 

int dss_install_mgr_ops(struct dss_device *dss,
			const struct dss_mgr_ops *mgr_ops,
			struct omap_drm_private *priv)
{
	if (dss->mgr_ops)
		return -EBUSY;

	dss->mgr_ops = mgr_ops;
	dss->mgr_ops_priv = priv;

	return 0;
}
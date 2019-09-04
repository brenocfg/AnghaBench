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
struct omap_dss_device {int /*<<< orphan*/  dispc_channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omap_dss_device*) ;} ;

/* Variables and functions */
 TYPE_1__* dss_mgr_ops ; 
 int /*<<< orphan*/  dss_mgr_ops_priv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omap_dss_device*) ; 

void dss_mgr_disconnect(struct omap_dss_device *dssdev,
			struct omap_dss_device *dst)
{
	dss_mgr_ops->disconnect(dss_mgr_ops_priv, dssdev->dispc_channel, dst);
}
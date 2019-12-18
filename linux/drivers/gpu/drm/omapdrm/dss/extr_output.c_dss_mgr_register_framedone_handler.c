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
struct omap_dss_device {int /*<<< orphan*/  dispc_channel; struct dss_device* dss; } ;
struct dss_device {int /*<<< orphan*/  mgr_ops_priv; TYPE_1__* mgr_ops; } ;
struct TYPE_2__ {int (* register_framedone_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*),void*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*),void*) ; 

int dss_mgr_register_framedone_handler(struct omap_dss_device *dssdev,
		void (*handler)(void *), void *data)
{
	struct dss_device *dss = dssdev->dss;

	return dss->mgr_ops->register_framedone_handler(dss->mgr_ops_priv,
							dssdev->dispc_channel,
							handler, data);
}
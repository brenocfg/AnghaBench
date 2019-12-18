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
struct dss_device {int /*<<< orphan*/ * dispc_ops; int /*<<< orphan*/ * dispc; } ;
struct dispc_device {int /*<<< orphan*/  debugfs; struct dss_device* dss; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct dispc_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dispc_errata_i734_wa_fini (struct dispc_device*) ; 
 int /*<<< orphan*/  dss_debugfs_remove_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dispc_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 

__attribute__((used)) static void dispc_unbind(struct device *dev, struct device *master, void *data)
{
	struct dispc_device *dispc = dev_get_drvdata(dev);
	struct dss_device *dss = dispc->dss;

	dss_debugfs_remove_file(dispc->debugfs);

	dss->dispc = NULL;
	dss->dispc_ops = NULL;

	pm_runtime_disable(dev);

	dispc_errata_i734_wa_fini(dispc);

	kfree(dispc);
}
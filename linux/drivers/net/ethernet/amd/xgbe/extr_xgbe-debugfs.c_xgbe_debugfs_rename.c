#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xgbe_prv_data {TYPE_3__* xgbe_debugfs; TYPE_1__* netdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_parent; TYPE_2__ d_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debugfs_rename (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

void xgbe_debugfs_rename(struct xgbe_prv_data *pdata)
{
	char *buf;

	if (!pdata->xgbe_debugfs)
		return;

	buf = kasprintf(GFP_KERNEL, "amd-xgbe-%s", pdata->netdev->name);
	if (!buf)
		return;

	if (!strcmp(pdata->xgbe_debugfs->d_name.name, buf))
		goto out;

	debugfs_rename(pdata->xgbe_debugfs->d_parent, pdata->xgbe_debugfs,
		       pdata->xgbe_debugfs->d_parent, buf);

out:
	kfree(buf);
}
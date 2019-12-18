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
struct dss_device {int /*<<< orphan*/ * mgr_ops_priv; int /*<<< orphan*/ * mgr_ops; } ;

/* Variables and functions */

void dss_uninstall_mgr_ops(struct dss_device *dss)
{
	dss->mgr_ops = NULL;
	dss->mgr_ops_priv = NULL;
}
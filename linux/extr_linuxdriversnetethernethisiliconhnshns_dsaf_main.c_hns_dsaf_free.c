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
struct dsaf_drv_priv {int /*<<< orphan*/ * soft_mac_tbl; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ hns_dsaf_dev_priv (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_remove_hw (struct dsaf_device*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_dsaf_free(struct dsaf_device *dsaf_dev)
{
	struct dsaf_drv_priv *priv =
	    (struct dsaf_drv_priv *)hns_dsaf_dev_priv(dsaf_dev);

	hns_dsaf_remove_hw(dsaf_dev);

	/* free all mac mem */
	vfree(priv->soft_mac_tbl);
	priv->soft_mac_tbl = NULL;
}
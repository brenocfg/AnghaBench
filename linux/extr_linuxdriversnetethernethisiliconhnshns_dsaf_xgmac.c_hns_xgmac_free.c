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
typedef  int /*<<< orphan*/  u32 ;
struct mac_driver {int /*<<< orphan*/  mac_id; int /*<<< orphan*/  dev; } ;
struct dsaf_device {TYPE_1__* misc_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* xge_srst ) (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_xgmac_free(void *mac_drv)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	struct dsaf_device *dsaf_dev
		= (struct dsaf_device *)dev_get_drvdata(drv->dev);

	u32 mac_id = drv->mac_id;

	dsaf_dev->misc_op->xge_srst(dsaf_dev, mac_id, 0);
}
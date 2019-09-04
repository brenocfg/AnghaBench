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
struct TYPE_2__ {int /*<<< orphan*/  (* xge_srst ) (struct dsaf_device*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_COMM_MODE_RX_AND_TX ; 
 scalar_t__ dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_xgmac_disable (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_xgmac_exc_irq_en (struct mac_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_xgmac_lf_rf_control_init (struct mac_driver*) ; 
 int /*<<< orphan*/  hns_xgmac_pma_fec_enable (struct mac_driver*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dsaf_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct dsaf_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_xgmac_init(void *mac_drv)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	struct dsaf_device *dsaf_dev
		= (struct dsaf_device *)dev_get_drvdata(drv->dev);
	u32 port = drv->mac_id;

	dsaf_dev->misc_op->xge_srst(dsaf_dev, port, 0);
	msleep(100);
	dsaf_dev->misc_op->xge_srst(dsaf_dev, port, 1);

	msleep(100);
	hns_xgmac_lf_rf_control_init(drv);
	hns_xgmac_exc_irq_en(drv, 0);

	hns_xgmac_pma_fec_enable(drv, 0x0, 0x0);

	hns_xgmac_disable(mac_drv, MAC_COMM_MODE_RX_AND_TX);
}
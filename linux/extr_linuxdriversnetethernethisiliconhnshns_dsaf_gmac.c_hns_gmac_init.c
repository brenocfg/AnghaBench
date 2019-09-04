#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mac_driver {TYPE_2__* mac_cb; int /*<<< orphan*/  mac_id; int /*<<< orphan*/  dev; } ;
struct dsaf_device {TYPE_1__* misc_op; } ;
struct TYPE_4__ {scalar_t__ mac_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ge_srst ) (struct dsaf_device*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_MODE_CHANGE_EB_B ; 
 int /*<<< orphan*/  GMAC_MODE_CHANGE_EN_REG ; 
 int /*<<< orphan*/  GMAC_TX_WATER_LINE_MASK ; 
 int /*<<< orphan*/  GMAC_TX_WATER_LINE_REG ; 
 int /*<<< orphan*/  GMAC_TX_WATER_LINE_SHIFT ; 
 scalar_t__ HNAE_PORT_DEBUG ; 
 int /*<<< orphan*/  MAC_COMM_MODE_RX_AND_TX ; 
 scalar_t__ dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_gmac_config_pad_and_crc (void*,int) ; 
 int /*<<< orphan*/  hns_gmac_disable (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_gmac_set_uc_match (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_gmac_tx_loop_pkt_dis (void*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct dsaf_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct dsaf_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_gmac_init(void *mac_drv)
{
	u32 port;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	struct dsaf_device *dsaf_dev
		= (struct dsaf_device *)dev_get_drvdata(drv->dev);

	port = drv->mac_id;

	dsaf_dev->misc_op->ge_srst(dsaf_dev, port, 0);
	mdelay(10);
	dsaf_dev->misc_op->ge_srst(dsaf_dev, port, 1);
	mdelay(10);
	hns_gmac_disable(mac_drv, MAC_COMM_MODE_RX_AND_TX);
	hns_gmac_tx_loop_pkt_dis(mac_drv);
	if (drv->mac_cb->mac_type == HNAE_PORT_DEBUG)
		hns_gmac_set_uc_match(mac_drv, 0);

	hns_gmac_config_pad_and_crc(mac_drv, 1);

	dsaf_set_dev_bit(drv, GMAC_MODE_CHANGE_EN_REG,
			 GMAC_MODE_CHANGE_EB_B, 1);

	/* reduce gmac tx water line to avoid gmac hang-up
	 * in speed 100M and duplex half.
	 */
	dsaf_set_dev_field(drv, GMAC_TX_WATER_LINE_REG, GMAC_TX_WATER_LINE_MASK,
			   GMAC_TX_WATER_LINE_SHIFT, 8);
}
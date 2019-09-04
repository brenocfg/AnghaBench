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
typedef  int /*<<< orphan*/  u32 ;
struct mac_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_TX_LOOP_PKT_EN_B ; 
 int /*<<< orphan*/  GMAC_TX_LOOP_PKT_HIG_PRI_B ; 
 int /*<<< orphan*/  GMAC_TX_LOOP_PKT_PRI_REG ; 
 int /*<<< orphan*/  dsaf_read_dev (struct mac_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_tx_loop_pkt_dis(void *mac_drv)
{
	u32 tx_loop_pkt_pri;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	tx_loop_pkt_pri = dsaf_read_dev(drv, GMAC_TX_LOOP_PKT_PRI_REG);
	dsaf_set_bit(tx_loop_pkt_pri, GMAC_TX_LOOP_PKT_EN_B, 1);
	dsaf_set_bit(tx_loop_pkt_pri, GMAC_TX_LOOP_PKT_HIG_PRI_B, 0);
	dsaf_write_dev(drv, GMAC_TX_LOOP_PKT_PRI_REG, tx_loop_pkt_pri);
}
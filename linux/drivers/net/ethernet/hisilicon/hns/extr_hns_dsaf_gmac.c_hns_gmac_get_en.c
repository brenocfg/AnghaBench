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
 int /*<<< orphan*/  GMAC_PORT_EN_REG ; 
 int /*<<< orphan*/  GMAC_PORT_RX_EN_B ; 
 int /*<<< orphan*/  GMAC_PORT_TX_EN_B ; 
 int /*<<< orphan*/  dsaf_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_read_dev (struct mac_driver*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_get_en(void *mac_drv, u32 *rx, u32 *tx)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	u32 porten;

	porten = dsaf_read_dev(drv, GMAC_PORT_EN_REG);
	*tx = dsaf_get_bit(porten, GMAC_PORT_TX_EN_B);
	*rx = dsaf_get_bit(porten, GMAC_PORT_RX_EN_B);
}
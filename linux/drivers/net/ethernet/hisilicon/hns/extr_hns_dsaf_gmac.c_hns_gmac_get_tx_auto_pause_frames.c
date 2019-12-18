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
typedef  int /*<<< orphan*/  u16 ;
struct mac_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_FC_TX_TIMER_M ; 
 int /*<<< orphan*/  GMAC_FC_TX_TIMER_REG ; 
 int /*<<< orphan*/  GMAC_FC_TX_TIMER_S ; 
 int /*<<< orphan*/  dsaf_get_dev_field (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_get_tx_auto_pause_frames(void *mac_drv, u16 *newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	*newval = dsaf_get_dev_field(drv, GMAC_FC_TX_TIMER_REG,
				     GMAC_FC_TX_TIMER_M, GMAC_FC_TX_TIMER_S);
}
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
typedef  int u32 ;
struct mac_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGMAC_INT_ENABLE_REG ; 
 int /*<<< orphan*/  XGMAC_INT_STATUS_REG ; 
 int /*<<< orphan*/  dsaf_write_dev (struct mac_driver*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_xgmac_exc_irq_en(struct mac_driver *drv, u32 en)
{
	u32 clr_vlue = 0xfffffffful;
	u32 msk_vlue = en ? 0xfffffffful : 0; /*1 is en, 0 is dis*/

	dsaf_write_dev(drv, XGMAC_INT_STATUS_REG, clr_vlue);
	dsaf_write_dev(drv, XGMAC_INT_ENABLE_REG, msk_vlue);
}
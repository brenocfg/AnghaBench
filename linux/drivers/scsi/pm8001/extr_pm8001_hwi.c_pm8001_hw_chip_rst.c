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
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPC_REG_RESET ; 
 int SPC_REG_RESET_DEVICE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pm8001_hw_chip_rst(struct pm8001_hba_info *pm8001_ha)
{
	u32 i;
	u32 regVal;
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("chip reset start\n"));

	/* do SPC chip reset. */
	regVal = pm8001_cr32(pm8001_ha, 1, SPC_REG_RESET);
	regVal &= ~(SPC_REG_RESET_DEVICE);
	pm8001_cw32(pm8001_ha, 1, SPC_REG_RESET, regVal);

	/* delay 10 usec */
	udelay(10);

	/* bring chip reset out of reset */
	regVal = pm8001_cr32(pm8001_ha, 1, SPC_REG_RESET);
	regVal |= SPC_REG_RESET_DEVICE;
	pm8001_cw32(pm8001_ha, 1, SPC_REG_RESET, regVal);

	/* delay 10 usec */
	udelay(10);

	/* wait for 20 msec until the firmware gets reloaded */
	i = 20;
	do {
		mdelay(1);
	} while ((--i) != 0);

	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("chip reset finished\n"));
}
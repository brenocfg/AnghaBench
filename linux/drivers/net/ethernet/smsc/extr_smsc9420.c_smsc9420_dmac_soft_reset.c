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
struct smsc9420_pdata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_MODE ; 
 int BUS_MODE_SWR_ ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_warn (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void smsc9420_dmac_soft_reset(struct smsc9420_pdata *pd)
{
	smsc9420_reg_write(pd, BUS_MODE, BUS_MODE_SWR_);
	smsc9420_reg_read(pd, BUS_MODE);
	udelay(2);
	if (smsc9420_reg_read(pd, BUS_MODE) & BUS_MODE_SWR_)
		netif_warn(pd, drv, pd->dev, "Software reset not cleared\n");
}
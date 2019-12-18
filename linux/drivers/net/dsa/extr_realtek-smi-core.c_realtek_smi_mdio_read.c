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
struct realtek_smi {TYPE_1__* ops; } ;
struct mii_bus {struct realtek_smi* priv; } ;
struct TYPE_2__ {int (* phy_read ) (struct realtek_smi*,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct realtek_smi*,int,int) ; 

__attribute__((used)) static int realtek_smi_mdio_read(struct mii_bus *bus, int addr, int regnum)
{
	struct realtek_smi *smi = bus->priv;

	return smi->ops->phy_read(smi, addr, regnum);
}
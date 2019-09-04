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
typedef  int /*<<< orphan*/  u16 ;
struct lan9303 {int phy_addr_base; TYPE_1__* ops; } ;
struct dsa_switch {struct lan9303* priv; } ;
struct TYPE_2__ {int (* phy_write ) (struct lan9303*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int lan9303_virt_phy_reg_write (struct lan9303*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct lan9303*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_phy_write(struct dsa_switch *ds, int phy, int regnum,
			     u16 val)
{
	struct lan9303 *chip = ds->priv;
	int phy_base = chip->phy_addr_base;

	if (phy == phy_base)
		return lan9303_virt_phy_reg_write(chip, regnum, val);
	if (phy > phy_base + 2)
		return -ENODEV;

	return chip->ops->phy_write(chip, phy, regnum, val);
}
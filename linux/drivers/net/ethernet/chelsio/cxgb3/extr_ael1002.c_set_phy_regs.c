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
struct reg_val {int clear_bits; int /*<<< orphan*/  set_bits; int /*<<< orphan*/  reg_addr; scalar_t__ mmd_addr; } ;
struct cphy {int dummy; } ;

/* Variables and functions */
 int t3_mdio_change_bits (struct cphy*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int t3_mdio_write (struct cphy*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_phy_regs(struct cphy *phy, const struct reg_val *rv)
{
	int err;

	for (err = 0; rv->mmd_addr && !err; rv++) {
		if (rv->clear_bits == 0xffff)
			err = t3_mdio_write(phy, rv->mmd_addr, rv->reg_addr,
					    rv->set_bits);
		else
			err = t3_mdio_change_bits(phy, rv->mmd_addr,
						  rv->reg_addr, rv->clear_bits,
						  rv->set_bits);
	}
	return err;
}
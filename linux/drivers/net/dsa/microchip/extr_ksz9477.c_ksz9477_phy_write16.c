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
struct ksz_device {int phy_port_cnt; int features; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int GBIT_SUPPORT ; 
 int MII_CTRL1000 ; 
 int /*<<< orphan*/  ksz_pwrite16 (struct ksz_device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ksz9477_phy_write16(struct dsa_switch *ds, int addr, int reg,
			       u16 val)
{
	struct ksz_device *dev = ds->priv;

	/* No real PHY after this. */
	if (addr >= dev->phy_port_cnt)
		return 0;

	/* No gigabit support.  Do not write to this register. */
	if (!(dev->features & GBIT_SUPPORT) && reg == MII_CTRL1000)
		return 0;
	ksz_pwrite16(dev, addr, 0x100 + (reg << 1), val);

	return 0;
}
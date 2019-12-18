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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct ksz_port {TYPE_1__ phydev; } ;
struct ksz_device {int phy_port_cnt; struct ksz_port* ports; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
#define  MII_ADVERTISE 135 
#define  MII_BMCR 134 
#define  MII_BMSR 133 
#define  MII_CTRL1000 132 
#define  MII_LPA 131 
#define  MII_PHYSID1 130 
#define  MII_PHYSID2 129 
#define  MII_STAT1000 128 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  ksz_pread16 (struct ksz_device*,int,int,int*) ; 

__attribute__((used)) static int ksz9477_phy_read16(struct dsa_switch *ds, int addr, int reg)
{
	struct ksz_device *dev = ds->priv;
	u16 val = 0xffff;

	/* No real PHY after this. Simulate the PHY.
	 * A fixed PHY can be setup in the device tree, but this function is
	 * still called for that port during initialization.
	 * For RGMII PHY there is no way to access it so the fixed PHY should
	 * be used.  For SGMII PHY the supporting code will be added later.
	 */
	if (addr >= dev->phy_port_cnt) {
		struct ksz_port *p = &dev->ports[addr];

		switch (reg) {
		case MII_BMCR:
			val = 0x1140;
			break;
		case MII_BMSR:
			val = 0x796d;
			break;
		case MII_PHYSID1:
			val = 0x0022;
			break;
		case MII_PHYSID2:
			val = 0x1631;
			break;
		case MII_ADVERTISE:
			val = 0x05e1;
			break;
		case MII_LPA:
			val = 0xc5e1;
			break;
		case MII_CTRL1000:
			val = 0x0700;
			break;
		case MII_STAT1000:
			if (p->phydev.speed == SPEED_1000)
				val = 0x3800;
			else
				val = 0;
			break;
		}
	} else {
		ksz_pread16(dev, addr, 0x100 + (reg << 1), &val);
	}

	return val;
}
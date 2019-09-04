#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {TYPE_2__* core; } ;
struct bgmac {TYPE_4__* net_dev; TYPE_3__ bcma; } ;
struct bcma_drv_cc {int dummy; } ;
struct bcma_chipinfo {scalar_t__ id; int pkg; } ;
struct TYPE_8__ {scalar_t__ phydev; } ;
struct TYPE_6__ {TYPE_1__* bus; } ;
struct TYPE_5__ {struct bcma_drv_cc drv_cc; struct bcma_chipinfo chipinfo; } ;

/* Variables and functions */
 scalar_t__ BCMA_CHIP_ID_BCM4749 ; 
 scalar_t__ BCMA_CHIP_ID_BCM5356 ; 
 scalar_t__ BCMA_CHIP_ID_BCM5357 ; 
 scalar_t__ BCMA_CHIP_ID_BCM53572 ; 
 int /*<<< orphan*/  bcma_chipco_chipctl_maskset (struct bcma_drv_cc*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_mdio_phy_write (struct bgmac*,int,int,int) ; 
 int /*<<< orphan*/  phy_init_hw (scalar_t__) ; 

__attribute__((used)) static void bcma_mdio_phy_init(struct bgmac *bgmac)
{
	struct bcma_chipinfo *ci = &bgmac->bcma.core->bus->chipinfo;
	u8 i;

	/* For some legacy hardware we do chipset-based PHY initialization here
	 * without even detecting PHY ID. It's hacky and should be cleaned as
	 * soon as someone can test it.
	 */
	if (ci->id == BCMA_CHIP_ID_BCM5356) {
		for (i = 0; i < 5; i++) {
			bcma_mdio_phy_write(bgmac, i, 0x1f, 0x008b);
			bcma_mdio_phy_write(bgmac, i, 0x15, 0x0100);
			bcma_mdio_phy_write(bgmac, i, 0x1f, 0x000f);
			bcma_mdio_phy_write(bgmac, i, 0x12, 0x2aaa);
			bcma_mdio_phy_write(bgmac, i, 0x1f, 0x000b);
		}
		return;
	}
	if ((ci->id == BCMA_CHIP_ID_BCM5357 && ci->pkg != 10) ||
	    (ci->id == BCMA_CHIP_ID_BCM4749 && ci->pkg != 10) ||
	    (ci->id == BCMA_CHIP_ID_BCM53572 && ci->pkg != 9)) {
		struct bcma_drv_cc *cc = &bgmac->bcma.core->bus->drv_cc;

		bcma_chipco_chipctl_maskset(cc, 2, ~0xc0000000, 0);
		bcma_chipco_chipctl_maskset(cc, 4, ~0x80000000, 0);
		for (i = 0; i < 5; i++) {
			bcma_mdio_phy_write(bgmac, i, 0x1f, 0x000f);
			bcma_mdio_phy_write(bgmac, i, 0x16, 0x5284);
			bcma_mdio_phy_write(bgmac, i, 0x1f, 0x000b);
			bcma_mdio_phy_write(bgmac, i, 0x17, 0x0010);
			bcma_mdio_phy_write(bgmac, i, 0x1f, 0x000f);
			bcma_mdio_phy_write(bgmac, i, 0x16, 0x5296);
			bcma_mdio_phy_write(bgmac, i, 0x17, 0x1073);
			bcma_mdio_phy_write(bgmac, i, 0x17, 0x9073);
			bcma_mdio_phy_write(bgmac, i, 0x16, 0x52b6);
			bcma_mdio_phy_write(bgmac, i, 0x17, 0x9273);
			bcma_mdio_phy_write(bgmac, i, 0x1f, 0x000b);
		}
		return;
	}

	/* For all other hw do initialization using PHY subsystem. */
	if (bgmac->net_dev && bgmac->net_dev->phydev)
		phy_init_hw(bgmac->net_dev->phydev);
}
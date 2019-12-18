#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct phy_table {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {size_t active; int useMII; int mii_cnt; TYPE_2__* phy; } ;
struct TYPE_7__ {int id; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct TYPE_6__ {int addr; int id; TYPE_1__ spd; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int DE4X5_MAX_MII ; 
 int DE4X5_MAX_PHY ; 
 int /*<<< orphan*/  DE4X5_MII ; 
 int DEBUG_MII ; 
 int /*<<< orphan*/  GENERIC_MASK ; 
 int /*<<< orphan*/  GENERIC_REG ; 
 int /*<<< orphan*/  GENERIC_VALUE ; 
 int /*<<< orphan*/  MII_CR ; 
 int MII_CR_RST ; 
 int /*<<< orphan*/  de4x5_dbg_mii (struct net_device*,int) ; 
 int de4x5_debug ; 
 scalar_t__ de4x5_reset_phy (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int mii_get_oui (int,int /*<<< orphan*/ ) ; 
 int mii_rd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_wr (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 TYPE_3__* phy_info ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
mii_get_phy(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int i, j, k, n, limit=ARRAY_SIZE(phy_info);
    int id;

    lp->active = 0;
    lp->useMII = true;

    /* Search the MII address space for possible PHY devices */
    for (n=0, lp->mii_cnt=0, i=1; !((i==1) && (n==1)); i=(i+1)%DE4X5_MAX_MII) {
	lp->phy[lp->active].addr = i;
	if (i==0) n++;                             /* Count cycles */
	while (de4x5_reset_phy(dev)<0) udelay(100);/* Wait for reset */
	id = mii_get_oui(i, DE4X5_MII);
	if ((id == 0) || (id == 65535)) continue;  /* Valid ID? */
	for (j=0; j<limit; j++) {                  /* Search PHY table */
	    if (id != phy_info[j].id) continue;    /* ID match? */
	    for (k=0; k < DE4X5_MAX_PHY && lp->phy[k].id; k++);
	    if (k < DE4X5_MAX_PHY) {
		memcpy((char *)&lp->phy[k],
		       (char *)&phy_info[j], sizeof(struct phy_table));
		lp->phy[k].addr = i;
		lp->mii_cnt++;
		lp->active++;
	    } else {
		goto purgatory;                    /* Stop the search */
	    }
	    break;
	}
	if ((j == limit) && (i < DE4X5_MAX_MII)) {
	    for (k=0; k < DE4X5_MAX_PHY && lp->phy[k].id; k++);
	    lp->phy[k].addr = i;
	    lp->phy[k].id = id;
	    lp->phy[k].spd.reg = GENERIC_REG;      /* ANLPA register         */
	    lp->phy[k].spd.mask = GENERIC_MASK;    /* 100Mb/s technologies   */
	    lp->phy[k].spd.value = GENERIC_VALUE;  /* TX & T4, H/F Duplex    */
	    lp->mii_cnt++;
	    lp->active++;
	    printk("%s: Using generic MII device control. If the board doesn't operate,\nplease mail the following dump to the author:\n", dev->name);
	    j = de4x5_debug;
	    de4x5_debug |= DEBUG_MII;
	    de4x5_dbg_mii(dev, k);
	    de4x5_debug = j;
	    printk("\n");
	}
    }
  purgatory:
    lp->active = 0;
    if (lp->phy[0].id) {                           /* Reset the PHY devices */
	for (k=0; k < DE4X5_MAX_PHY && lp->phy[k].id; k++) { /*For each PHY*/
	    mii_wr(MII_CR_RST, MII_CR, lp->phy[k].addr, DE4X5_MII);
	    while (mii_rd(MII_CR, lp->phy[k].addr, DE4X5_MII) & MII_CR_RST);

	    de4x5_dbg_mii(dev, k);
	}
    }
    if (!lp->mii_cnt) lp->useMII = false;

    return lp->mii_cnt;
}
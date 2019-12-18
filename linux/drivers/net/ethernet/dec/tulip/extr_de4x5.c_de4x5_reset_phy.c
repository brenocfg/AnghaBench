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
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {size_t active; scalar_t__ timeout; scalar_t__ chipset; scalar_t__ useMII; TYPE_1__* phy; scalar_t__ rst; scalar_t__ useSROM; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; scalar_t__ rst; scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ DC21140 ; 
 int /*<<< orphan*/  DE4X5_MII ; 
 int /*<<< orphan*/  MII_CR ; 
 int /*<<< orphan*/  MII_CR_RST ; 
 int /*<<< orphan*/  PHY_HARD_RESET ; 
 int /*<<< orphan*/  mii_wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  srom_exec (struct net_device*,scalar_t__) ; 
 int test_mii_reg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
de4x5_reset_phy(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int next_tick = 0;

    if ((lp->useSROM) || (lp->phy[lp->active].id)) {
	if (lp->timeout < 0) {
	    if (lp->useSROM) {
		if (lp->phy[lp->active].rst) {
		    srom_exec(dev, lp->phy[lp->active].rst);
		    srom_exec(dev, lp->phy[lp->active].rst);
		} else if (lp->rst) {          /* Type 5 infoblock reset */
		    srom_exec(dev, lp->rst);
		    srom_exec(dev, lp->rst);
		}
	    } else {
		PHY_HARD_RESET;
	    }
	    if (lp->useMII) {
	        mii_wr(MII_CR_RST, MII_CR, lp->phy[lp->active].addr, DE4X5_MII);
            }
        }
	if (lp->useMII) {
	    next_tick = test_mii_reg(dev, MII_CR, MII_CR_RST, false, 500);
	}
    } else if (lp->chipset == DC21140) {
	PHY_HARD_RESET;
    }

    return next_tick;
}
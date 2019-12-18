#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct phy_device {int speed; scalar_t__ duplex; int /*<<< orphan*/  link; } ;
struct TYPE_4__ {int desc_split; } ;
struct ag71xx {int* fifodata; TYPE_2__ tx_ring; TYPE_1__* ndev; } ;
struct TYPE_3__ {struct phy_device* phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_FIFO_CFG3 ; 
 int /*<<< orphan*/  AG71XX_REG_FIFO_CFG5 ; 
 int /*<<< orphan*/  AG71XX_REG_MAC_CFG2 ; 
 int /*<<< orphan*/  AG71XX_REG_MAC_IFCTL ; 
 int /*<<< orphan*/  AR7100 ; 
 int /*<<< orphan*/  AR9130 ; 
 int FIFO_CFG5_BM ; 
 int MAC_CFG2_FDX ; 
 int MAC_CFG2_IF_1000 ; 
 int MAC_CFG2_IF_10_100 ; 
 int MAC_IFCTL_SPEED ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  ag71xx_fast_reset (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_start (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_stop (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_is (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int ag71xx_rr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void ag71xx_link_adjust(struct ag71xx *ag, bool update)
{
	struct phy_device *phydev = ag->ndev->phydev;
	u32 cfg2;
	u32 ifctl;
	u32 fifo5;

	if (!phydev->link && update) {
		ag71xx_hw_stop(ag);
		return;
	}

	if (!ag71xx_is(ag, AR7100) && !ag71xx_is(ag, AR9130))
		ag71xx_fast_reset(ag);

	cfg2 = ag71xx_rr(ag, AG71XX_REG_MAC_CFG2);
	cfg2 &= ~(MAC_CFG2_IF_1000 | MAC_CFG2_IF_10_100 | MAC_CFG2_FDX);
	cfg2 |= (phydev->duplex) ? MAC_CFG2_FDX : 0;

	ifctl = ag71xx_rr(ag, AG71XX_REG_MAC_IFCTL);
	ifctl &= ~(MAC_IFCTL_SPEED);

	fifo5 = ag71xx_rr(ag, AG71XX_REG_FIFO_CFG5);
	fifo5 &= ~FIFO_CFG5_BM;

	switch (phydev->speed) {
	case SPEED_1000:
		cfg2 |= MAC_CFG2_IF_1000;
		fifo5 |= FIFO_CFG5_BM;
		break;
	case SPEED_100:
		cfg2 |= MAC_CFG2_IF_10_100;
		ifctl |= MAC_IFCTL_SPEED;
		break;
	case SPEED_10:
		cfg2 |= MAC_CFG2_IF_10_100;
		break;
	default:
		WARN(1, "not supported speed %i\n", phydev->speed);
		return;
	}

	if (ag->tx_ring.desc_split) {
		ag->fifodata[2] &= 0xffff;
		ag->fifodata[2] |= ((2048 - ag->tx_ring.desc_split) / 4) << 16;
	}

	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG3, ag->fifodata[2]);

	ag71xx_wr(ag, AG71XX_REG_MAC_CFG2, cfg2);
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG5, fifo5);
	ag71xx_wr(ag, AG71XX_REG_MAC_IFCTL, ifctl);

	ag71xx_hw_start(ag);

	if (update)
		phy_print_status(phydev);
}
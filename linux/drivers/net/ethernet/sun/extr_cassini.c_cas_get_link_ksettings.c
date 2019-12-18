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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int duplex; void* speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;
struct cas {int cas_flags; int lstate; int link_cntl; int /*<<< orphan*/  lock; scalar_t__ regs; scalar_t__ hw_running; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  phy_type; } ;
typedef  enum link_state { ____Placeholder_link_state } link_state ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_MII ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int CAS_BMCR_SPEED1000 ; 
 int CAS_FLAG_1000MB_CAP ; 
 scalar_t__ CAS_PHY_MII (int /*<<< orphan*/ ) ; 
 void* DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_MII ; 
 scalar_t__ REG_PCS_MII_CTRL ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  cas_mif_poll (struct cas*,int) ; 
 int cas_phy_read (struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_read_mii_link_mode (struct cas*,int*,int*,int*) ; 
 int /*<<< orphan*/  cas_read_pcs_link_mode (struct cas*,int*,int*,int*) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int link_up ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cas_get_link_ksettings(struct net_device *dev,
				  struct ethtool_link_ksettings *cmd)
{
	struct cas *cp = netdev_priv(dev);
	u16 bmcr;
	int full_duplex, speed, pause;
	unsigned long flags;
	enum link_state linkstate = link_up;
	u32 supported, advertising;

	advertising = 0;
	supported = SUPPORTED_Autoneg;
	if (cp->cas_flags & CAS_FLAG_1000MB_CAP) {
		supported |= SUPPORTED_1000baseT_Full;
		advertising |= ADVERTISED_1000baseT_Full;
	}

	/* Record PHY settings if HW is on. */
	spin_lock_irqsave(&cp->lock, flags);
	bmcr = 0;
	linkstate = cp->lstate;
	if (CAS_PHY_MII(cp->phy_type)) {
		cmd->base.port = PORT_MII;
		cmd->base.phy_address = cp->phy_addr;
		advertising |= ADVERTISED_TP | ADVERTISED_MII |
			ADVERTISED_10baseT_Half |
			ADVERTISED_10baseT_Full |
			ADVERTISED_100baseT_Half |
			ADVERTISED_100baseT_Full;

		supported |=
			(SUPPORTED_10baseT_Half |
			 SUPPORTED_10baseT_Full |
			 SUPPORTED_100baseT_Half |
			 SUPPORTED_100baseT_Full |
			 SUPPORTED_TP | SUPPORTED_MII);

		if (cp->hw_running) {
			cas_mif_poll(cp, 0);
			bmcr = cas_phy_read(cp, MII_BMCR);
			cas_read_mii_link_mode(cp, &full_duplex,
					       &speed, &pause);
			cas_mif_poll(cp, 1);
		}

	} else {
		cmd->base.port = PORT_FIBRE;
		cmd->base.phy_address = 0;
		supported   |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;

		if (cp->hw_running) {
			/* pcs uses the same bits as mii */
			bmcr = readl(cp->regs + REG_PCS_MII_CTRL);
			cas_read_pcs_link_mode(cp, &full_duplex,
					       &speed, &pause);
		}
	}
	spin_unlock_irqrestore(&cp->lock, flags);

	if (bmcr & BMCR_ANENABLE) {
		advertising |= ADVERTISED_Autoneg;
		cmd->base.autoneg = AUTONEG_ENABLE;
		cmd->base.speed =  ((speed == 10) ?
					    SPEED_10 :
					    ((speed == 1000) ?
					     SPEED_1000 : SPEED_100));
		cmd->base.duplex = full_duplex ? DUPLEX_FULL : DUPLEX_HALF;
	} else {
		cmd->base.autoneg = AUTONEG_DISABLE;
		cmd->base.speed = ((bmcr & CAS_BMCR_SPEED1000) ?
					    SPEED_1000 :
					    ((bmcr & BMCR_SPEED100) ?
					     SPEED_100 : SPEED_10));
		cmd->base.duplex = (bmcr & BMCR_FULLDPLX) ?
			DUPLEX_FULL : DUPLEX_HALF;
	}
	if (linkstate != link_up) {
		/* Force these to "unknown" if the link is not up and
		 * autonogotiation in enabled. We can set the link
		 * speed to 0, but not cmd->duplex,
		 * because its legal values are 0 and 1.  Ethtool will
		 * print the value reported in parentheses after the
		 * word "Unknown" for unrecognized values.
		 *
		 * If in forced mode, we report the speed and duplex
		 * settings that we configured.
		 */
		if (cp->link_cntl & BMCR_ANENABLE) {
			cmd->base.speed = 0;
			cmd->base.duplex = 0xff;
		} else {
			cmd->base.speed = SPEED_10;
			if (cp->link_cntl & BMCR_SPEED100) {
				cmd->base.speed = SPEED_100;
			} else if (cp->link_cntl & CAS_BMCR_SPEED1000) {
				cmd->base.speed = SPEED_1000;
			}
			cmd->base.duplex = (cp->link_cntl & BMCR_FULLDPLX) ?
				DUPLEX_FULL : DUPLEX_HALF;
		}
	}

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}
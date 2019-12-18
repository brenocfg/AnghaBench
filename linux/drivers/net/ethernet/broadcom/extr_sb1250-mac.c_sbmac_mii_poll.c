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
struct sbmac_softc {scalar_t__ sbm_link; scalar_t__ sbm_speed; scalar_t__ sbm_duplex; int sbm_pause; int sbm_fc; scalar_t__ sbm_state; int /*<<< orphan*/  sbm_lock; struct phy_device* phy_dev; } ;
struct phy_device {scalar_t__ link; scalar_t__ speed; scalar_t__ duplex; int pause; } ;
struct net_device {int /*<<< orphan*/  name; } ;
typedef  enum sbmac_fc { ____Placeholder_sbmac_fc } sbmac_fc ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int debug ; 
 struct sbmac_softc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sbmac_channel_start (struct sbmac_softc*) ; 
 int /*<<< orphan*/  sbmac_channel_stop (struct sbmac_softc*) ; 
 scalar_t__ sbmac_duplex_none ; 
 int sbmac_fc_collision ; 
 void* sbmac_fc_disabled ; 
 int sbmac_fc_frame ; 
 scalar_t__ sbmac_speed_none ; 
 scalar_t__ sbmac_state_off ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sbmac_mii_poll(struct net_device *dev)
{
	struct sbmac_softc *sc = netdev_priv(dev);
	struct phy_device *phy_dev = sc->phy_dev;
	unsigned long flags;
	enum sbmac_fc fc;
	int link_chg, speed_chg, duplex_chg, pause_chg, fc_chg;

	link_chg = (sc->sbm_link != phy_dev->link);
	speed_chg = (sc->sbm_speed != phy_dev->speed);
	duplex_chg = (sc->sbm_duplex != phy_dev->duplex);
	pause_chg = (sc->sbm_pause != phy_dev->pause);

	if (!link_chg && !speed_chg && !duplex_chg && !pause_chg)
		return;					/* Hmmm... */

	if (!phy_dev->link) {
		if (link_chg) {
			sc->sbm_link = phy_dev->link;
			sc->sbm_speed = sbmac_speed_none;
			sc->sbm_duplex = sbmac_duplex_none;
			sc->sbm_fc = sbmac_fc_disabled;
			sc->sbm_pause = -1;
			pr_info("%s: link unavailable\n", dev->name);
		}
		return;
	}

	if (phy_dev->duplex == DUPLEX_FULL) {
		if (phy_dev->pause)
			fc = sbmac_fc_frame;
		else
			fc = sbmac_fc_disabled;
	} else
		fc = sbmac_fc_collision;
	fc_chg = (sc->sbm_fc != fc);

	pr_info("%s: link available: %dbase-%cD\n", dev->name, phy_dev->speed,
		phy_dev->duplex == DUPLEX_FULL ? 'F' : 'H');

	spin_lock_irqsave(&sc->sbm_lock, flags);

	sc->sbm_speed = phy_dev->speed;
	sc->sbm_duplex = phy_dev->duplex;
	sc->sbm_fc = fc;
	sc->sbm_pause = phy_dev->pause;
	sc->sbm_link = phy_dev->link;

	if ((speed_chg || duplex_chg || fc_chg) &&
	    sc->sbm_state != sbmac_state_off) {
		/*
		 * something changed, restart the channel
		 */
		if (debug > 1)
			pr_debug("%s: restarting channel "
				 "because PHY state changed\n", dev->name);
		sbmac_channel_stop(sc);
		sbmac_channel_start(sc);
	}

	spin_unlock_irqrestore(&sc->sbm_lock, flags);
}
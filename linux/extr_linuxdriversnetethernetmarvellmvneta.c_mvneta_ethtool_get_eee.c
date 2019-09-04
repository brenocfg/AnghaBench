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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mvneta_port {int /*<<< orphan*/  phylink; int /*<<< orphan*/  tx_lpi_enabled; int /*<<< orphan*/  eee_active; int /*<<< orphan*/  eee_enabled; } ;
struct ethtool_eee {int tx_lpi_timer; int /*<<< orphan*/  tx_lpi_enabled; int /*<<< orphan*/  eee_active; int /*<<< orphan*/  eee_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_LPI_CTRL_0 ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int phylink_ethtool_get_eee (int /*<<< orphan*/ ,struct ethtool_eee*) ; 

__attribute__((used)) static int mvneta_ethtool_get_eee(struct net_device *dev,
				  struct ethtool_eee *eee)
{
	struct mvneta_port *pp = netdev_priv(dev);
	u32 lpi_ctl0;

	lpi_ctl0 = mvreg_read(pp, MVNETA_LPI_CTRL_0);

	eee->eee_enabled = pp->eee_enabled;
	eee->eee_active = pp->eee_active;
	eee->tx_lpi_enabled = pp->tx_lpi_enabled;
	eee->tx_lpi_timer = (lpi_ctl0) >> 8; // * scale;

	return phylink_ethtool_get_eee(pp->phylink, eee);
}
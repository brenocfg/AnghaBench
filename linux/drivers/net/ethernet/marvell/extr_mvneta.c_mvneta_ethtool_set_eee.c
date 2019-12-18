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
struct mvneta_port {int /*<<< orphan*/  phylink; scalar_t__ tx_lpi_enabled; scalar_t__ eee_enabled; } ;
struct ethtool_eee {int tx_lpi_timer; scalar_t__ eee_enabled; scalar_t__ tx_lpi_enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MVNETA_LPI_CTRL_0 ; 
 int /*<<< orphan*/  mvneta_set_eee (struct mvneta_port*,int) ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int phylink_ethtool_set_eee (int /*<<< orphan*/ ,struct ethtool_eee*) ; 

__attribute__((used)) static int mvneta_ethtool_set_eee(struct net_device *dev,
				  struct ethtool_eee *eee)
{
	struct mvneta_port *pp = netdev_priv(dev);
	u32 lpi_ctl0;

	/* The Armada 37x documents do not give limits for this other than
	 * it being an 8-bit register. */
	if (eee->tx_lpi_enabled && eee->tx_lpi_timer > 255)
		return -EINVAL;

	lpi_ctl0 = mvreg_read(pp, MVNETA_LPI_CTRL_0);
	lpi_ctl0 &= ~(0xff << 8);
	lpi_ctl0 |= eee->tx_lpi_timer << 8;
	mvreg_write(pp, MVNETA_LPI_CTRL_0, lpi_ctl0);

	pp->eee_enabled = eee->eee_enabled;
	pp->tx_lpi_enabled = eee->tx_lpi_enabled;

	mvneta_set_eee(pp, eee->tx_lpi_enabled && eee->eee_enabled);

	return phylink_ethtool_set_eee(pp->phylink, eee);
}
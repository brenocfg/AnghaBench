#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct mvpp2_port {int ntxqs; int nrxqs; } ;
struct TYPE_6__ {char* string; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 TYPE_1__* mvpp2_ethtool_mib_regs ; 
 TYPE_1__* mvpp2_ethtool_port_regs ; 
 TYPE_1__* mvpp2_ethtool_rxq_regs ; 
 TYPE_1__* mvpp2_ethtool_txq_regs ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_ethtool_get_strings(struct net_device *netdev, u32 sset,
				      u8 *data)
{
	struct mvpp2_port *port = netdev_priv(netdev);
	int i, q;

	if (sset != ETH_SS_STATS)
		return;

	for (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_mib_regs); i++) {
		strscpy(data, mvpp2_ethtool_mib_regs[i].string,
			ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	}

	for (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_port_regs); i++) {
		strscpy(data, mvpp2_ethtool_port_regs[i].string,
			ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	}

	for (q = 0; q < port->ntxqs; q++) {
		for (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_txq_regs); i++) {
			snprintf(data, ETH_GSTRING_LEN,
				 mvpp2_ethtool_txq_regs[i].string, q);
			data += ETH_GSTRING_LEN;
		}
	}

	for (q = 0; q < port->nrxqs; q++) {
		for (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_rxq_regs); i++) {
			snprintf(data, ETH_GSTRING_LEN,
				 mvpp2_ethtool_rxq_regs[i].string,
				 q);
			data += ETH_GSTRING_LEN;
		}
	}
}
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
struct mvpp2_port {struct mvpp2_ethtool_fs** rfs_rules; } ;
struct mvpp2_ethtool_fs {int /*<<< orphan*/  rxnfc; } ;
struct TYPE_2__ {size_t location; } ;
struct ethtool_rxnfc {TYPE_1__ fs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 size_t MVPP2_N_RFS_ENTRIES_PER_FLOW ; 
 int /*<<< orphan*/  memcpy (struct ethtool_rxnfc*,int /*<<< orphan*/ *,int) ; 

int mvpp2_ethtool_cls_rule_get(struct mvpp2_port *port,
			       struct ethtool_rxnfc *rxnfc)
{
	struct mvpp2_ethtool_fs *efs;

	if (rxnfc->fs.location >= MVPP2_N_RFS_ENTRIES_PER_FLOW)
		return -EINVAL;

	efs = port->rfs_rules[rxnfc->fs.location];
	if (!efs)
		return -ENOENT;

	memcpy(rxnfc, &efs->rxnfc, sizeof(efs->rxnfc));

	return 0;
}
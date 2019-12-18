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
struct mvpp2_port {struct mvpp2_ethtool_fs** rfs_rules; int /*<<< orphan*/  n_rfs_rules; } ;
struct mvpp2_ethtool_fs {int /*<<< orphan*/  rule; } ;
struct TYPE_2__ {size_t location; } ;
struct ethtool_rxnfc {TYPE_1__ fs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (struct mvpp2_ethtool_fs*) ; 
 int mvpp2_port_cls_rfs_rule_remove (struct mvpp2_port*,int /*<<< orphan*/ *) ; 

int mvpp2_ethtool_cls_rule_del(struct mvpp2_port *port,
			       struct ethtool_rxnfc *info)
{
	struct mvpp2_ethtool_fs *efs;
	int ret;

	efs = port->rfs_rules[info->fs.location];
	if (!efs)
		return -EINVAL;

	/* Remove the rule from the engines. */
	ret = mvpp2_port_cls_rfs_rule_remove(port, &efs->rule);
	if (ret)
		return ret;

	port->n_rfs_rules--;
	port->rfs_rules[info->fs.location] = NULL;
	kfree(efs);

	return 0;
}
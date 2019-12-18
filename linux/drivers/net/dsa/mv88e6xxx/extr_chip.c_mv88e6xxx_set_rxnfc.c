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
struct mv88e6xxx_policy {int /*<<< orphan*/  action; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  policies; } ;
struct ethtool_rx_flow_spec {int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {int cmd; struct ethtool_rx_flow_spec fs; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 129 
#define  ETHTOOL_SRXCLSRLINS 128 
 int /*<<< orphan*/  MV88E6XXX_POLICY_ACTION_NORMAL ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct mv88e6xxx_policy*) ; 
 struct mv88e6xxx_policy* idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_policy_apply (struct mv88e6xxx_chip*,int,struct mv88e6xxx_policy*) ; 
 int mv88e6xxx_policy_insert (struct mv88e6xxx_chip*,int,struct ethtool_rx_flow_spec*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_set_rxnfc(struct dsa_switch *ds, int port,
			       struct ethtool_rxnfc *rxnfc)
{
	struct ethtool_rx_flow_spec *fs = &rxnfc->fs;
	struct mv88e6xxx_chip *chip = ds->priv;
	struct mv88e6xxx_policy *policy;
	int err;

	mv88e6xxx_reg_lock(chip);

	switch (rxnfc->cmd) {
	case ETHTOOL_SRXCLSRLINS:
		err = mv88e6xxx_policy_insert(chip, port, fs);
		break;
	case ETHTOOL_SRXCLSRLDEL:
		err = -ENOENT;
		policy = idr_remove(&chip->policies, fs->location);
		if (policy) {
			policy->action = MV88E6XXX_POLICY_ACTION_NORMAL;
			err = mv88e6xxx_policy_apply(chip, port, policy);
			devm_kfree(chip->dev, policy);
		}
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	mv88e6xxx_reg_unlock(chip);

	return err;
}
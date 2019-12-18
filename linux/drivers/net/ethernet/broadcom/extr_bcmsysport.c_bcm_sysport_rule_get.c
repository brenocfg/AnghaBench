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
struct TYPE_2__ {int /*<<< orphan*/  ring_cookie; int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {TYPE_1__ fs; } ;
struct bcm_sysport_priv {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  RX_CLS_FLOW_WAKE ; 
 int bcm_sysport_rule_find (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sysport_rule_get(struct bcm_sysport_priv *priv,
				struct ethtool_rxnfc *nfc)
{
	int index;

	/* This is not a rule that we know about */
	index = bcm_sysport_rule_find(priv, nfc->fs.location);
	if (index < 0)
		return -EOPNOTSUPP;

	nfc->fs.ring_cookie = RX_CLS_FLOW_WAKE;

	return 0;
}
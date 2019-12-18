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
struct TYPE_3__ {scalar_t__* data; scalar_t__ vlan_etype; } ;
struct ethtool_rx_flow_spec {int flow_type; scalar_t__ location; TYPE_1__ m_ext; } ;
struct dsa_switch {int dummy; } ;
struct cfp_rule {int port; int /*<<< orphan*/  next; int /*<<< orphan*/  fs; } ;
struct TYPE_4__ {int /*<<< orphan*/  rules_list; int /*<<< orphan*/  used; } ;
struct bcm_sf2_priv {TYPE_2__ cfp; } ;

/* Variables and functions */
 scalar_t__ CFP_NUM_RULES ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FLOW_EXT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RX_CLS_LOC_ANY ; 
 int bcm_sf2_cfp_rule_cmp (struct bcm_sf2_priv*,int,struct ethtool_rx_flow_spec*) ; 
 int bcm_sf2_cfp_rule_insert (struct dsa_switch*,int,struct ethtool_rx_flow_spec*) ; 
 scalar_t__ bcm_sf2_cfp_rule_size (struct bcm_sf2_priv*) ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 int /*<<< orphan*/  kfree (struct cfp_rule*) ; 
 struct cfp_rule* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ethtool_rx_flow_spec*,int) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sf2_cfp_rule_set(struct dsa_switch *ds, int port,
				struct ethtool_rx_flow_spec *fs)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	struct cfp_rule *rule = NULL;
	int ret = -EINVAL;

	/* Check for unsupported extensions */
	if ((fs->flow_type & FLOW_EXT) && (fs->m_ext.vlan_etype ||
	     fs->m_ext.data[1]))
		return -EINVAL;

	if (fs->location != RX_CLS_LOC_ANY && fs->location >= CFP_NUM_RULES)
		return -EINVAL;

	if (fs->location != RX_CLS_LOC_ANY &&
	    test_bit(fs->location, priv->cfp.used))
		return -EBUSY;

	if (fs->location != RX_CLS_LOC_ANY &&
	    fs->location > bcm_sf2_cfp_rule_size(priv))
		return -EINVAL;

	ret = bcm_sf2_cfp_rule_cmp(priv, port, fs);
	if (ret == 0)
		return -EEXIST;

	rule = kzalloc(sizeof(*rule), GFP_KERNEL);
	if (!rule)
		return -ENOMEM;

	ret = bcm_sf2_cfp_rule_insert(ds, port, fs);
	if (ret) {
		kfree(rule);
		return ret;
	}

	rule->port = port;
	memcpy(&rule->fs, fs, sizeof(*fs));
	list_add_tail(&rule->next, &priv->cfp.rules_list);

	return ret;
}
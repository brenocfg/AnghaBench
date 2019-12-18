#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {int /*<<< orphan*/  data; TYPE_1__ fs; } ;
struct cfp_rule {int /*<<< orphan*/  fs; } ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct cfp_rule* bcm_sf2_cfp_rule_find (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_rule_size (struct bcm_sf2_priv*) ; 
 int /*<<< orphan*/  bcm_sf2_invert_masks (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int bcm_sf2_cfp_rule_get(struct bcm_sf2_priv *priv, int port,
				struct ethtool_rxnfc *nfc)
{
	struct cfp_rule *rule;

	rule = bcm_sf2_cfp_rule_find(priv, port, nfc->fs.location);
	if (!rule)
		return -EINVAL;

	memcpy(&nfc->fs, &rule->fs, sizeof(rule->fs));

	bcm_sf2_invert_masks(&nfc->fs);

	/* Put the TCAM size here */
	nfc->data = bcm_sf2_cfp_rule_size(priv);

	return 0;
}
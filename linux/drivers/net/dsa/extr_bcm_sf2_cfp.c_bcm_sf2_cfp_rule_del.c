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
typedef  scalar_t__ u32 ;
struct cfp_rule {int /*<<< orphan*/  next; } ;
struct TYPE_2__ {int /*<<< orphan*/  unique; } ;
struct bcm_sf2_priv {TYPE_1__ cfp; } ;

/* Variables and functions */
 scalar_t__ CFP_NUM_RULES ; 
 int EINVAL ; 
 struct cfp_rule* bcm_sf2_cfp_rule_find (struct bcm_sf2_priv*,int,scalar_t__) ; 
 int bcm_sf2_cfp_rule_remove (struct bcm_sf2_priv*,int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cfp_rule*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sf2_cfp_rule_del(struct bcm_sf2_priv *priv, int port, u32 loc)
{
	struct cfp_rule *rule;
	int ret;

	if (loc >= CFP_NUM_RULES)
		return -EINVAL;

	/* Refuse deleting unused rules, and those that are not unique since
	 * that could leave IPv6 rules with one of the chained rule in the
	 * table.
	 */
	if (!test_bit(loc, priv->cfp.unique) || loc == 0)
		return -EINVAL;

	rule = bcm_sf2_cfp_rule_find(priv, port, loc);
	if (!rule)
		return -EINVAL;

	ret = bcm_sf2_cfp_rule_remove(priv, port, loc);

	list_del(&rule->next);
	kfree(rule);

	return ret;
}
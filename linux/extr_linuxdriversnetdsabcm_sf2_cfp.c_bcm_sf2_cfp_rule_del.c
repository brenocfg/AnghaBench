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
struct TYPE_2__ {int /*<<< orphan*/  unique; } ;
struct bcm_sf2_priv {TYPE_1__ cfp; } ;

/* Variables and functions */
 int EINVAL ; 
 int bcm_sf2_cfp_rule_del_one (struct bcm_sf2_priv*,int,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sf2_cfp_rule_del(struct bcm_sf2_priv *priv, int port,
				u32 loc)
{
	u32 next_loc = 0;
	int ret;

	/* Refuse deleting unused rules, and those that are not unique since
	 * that could leave IPv6 rules with one of the chained rule in the
	 * table.
	 */
	if (!test_bit(loc, priv->cfp.unique) || loc == 0)
		return -EINVAL;

	ret = bcm_sf2_cfp_rule_del_one(priv, port, loc, &next_loc);
	if (ret)
		return ret;

	/* If this was an IPv6 rule, delete is companion rule too */
	if (next_loc)
		ret = bcm_sf2_cfp_rule_del_one(priv, port, next_loc, NULL);

	return ret;
}
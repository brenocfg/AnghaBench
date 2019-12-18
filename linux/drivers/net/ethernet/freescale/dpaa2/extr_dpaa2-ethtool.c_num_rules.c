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
struct dpaa2_eth_priv {TYPE_1__* cls_rules; } ;
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */
 int dpaa2_eth_fs_count (struct dpaa2_eth_priv*) ; 

__attribute__((used)) static int num_rules(struct dpaa2_eth_priv *priv)
{
	int i, rules = 0;

	for (i = 0; i < dpaa2_eth_fs_count(priv); i++)
		if (priv->cls_rules[i].in_use)
			rules++;

	return rules;
}
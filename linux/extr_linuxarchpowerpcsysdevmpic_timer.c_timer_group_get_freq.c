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
typedef  int u32 ;
struct timer_group_priv {int flags; int timerfreq; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FSL_GLOBAL_TIMER ; 
 int MPIC_TIMER_TCR_CLKDIV ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int timer_group_get_freq(struct device_node *np,
			struct timer_group_priv *priv)
{
	u32 div;

	if (priv->flags & FSL_GLOBAL_TIMER) {
		struct device_node *dn;

		dn = of_find_compatible_node(NULL, NULL, "fsl,mpic");
		if (dn) {
			of_property_read_u32(dn, "clock-frequency",
					&priv->timerfreq);
			of_node_put(dn);
		}
	}

	if (priv->timerfreq <= 0)
		return -EINVAL;

	if (priv->flags & FSL_GLOBAL_TIMER) {
		div = (1 << (MPIC_TIMER_TCR_CLKDIV >> 8)) * 8;
		priv->timerfreq /= div;
	}

	return 0;
}
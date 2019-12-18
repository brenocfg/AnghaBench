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
struct bcm_sf2_priv {unsigned int num_cfp_rules; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int bcm_sf2_cfp_rule_size(struct bcm_sf2_priv *priv)
{
	/* Entry #0 is reserved */
	return priv->num_cfp_rules - 1;
}
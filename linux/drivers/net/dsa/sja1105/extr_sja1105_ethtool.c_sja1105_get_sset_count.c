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
struct sja1105_private {TYPE_1__* info; } ;
struct dsa_switch {struct sja1105_private* priv; } ;
struct TYPE_2__ {scalar_t__ device_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int ETH_SS_STATS ; 
 scalar_t__ SJA1105PR_DEVICE_ID ; 
 scalar_t__ SJA1105QS_DEVICE_ID ; 
 int /*<<< orphan*/  sja1105_port_stats ; 
 int /*<<< orphan*/  sja1105pqrs_extra_port_stats ; 

int sja1105_get_sset_count(struct dsa_switch *ds, int port, int sset)
{
	int count = ARRAY_SIZE(sja1105_port_stats);
	struct sja1105_private *priv = ds->priv;

	if (sset != ETH_SS_STATS)
		return -EOPNOTSUPP;

	if (priv->info->device_id == SJA1105PR_DEVICE_ID ||
	    priv->info->device_id == SJA1105QS_DEVICE_ID)
		count += ARRAY_SIZE(sja1105pqrs_extra_port_stats);

	return count;
}
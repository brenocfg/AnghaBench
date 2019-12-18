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
struct realtek_smi {int num_ports; int num_mib_counters; } ;
struct dsa_switch {struct realtek_smi* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_SS_STATS ; 

int rtl8366_get_sset_count(struct dsa_switch *ds, int port, int sset)
{
	struct realtek_smi *smi = ds->priv;

	/* We only support SS_STATS */
	if (sset != ETH_SS_STATS)
		return 0;
	if (port >= smi->num_ports)
		return -EINVAL;

	return smi->num_mib_counters;
}
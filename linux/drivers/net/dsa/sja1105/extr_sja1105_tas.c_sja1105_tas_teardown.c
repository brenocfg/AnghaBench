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
struct tc_taprio_qopt_offload {int dummy; } ;
struct TYPE_2__ {struct tc_taprio_qopt_offload** offload; } ;
struct sja1105_private {TYPE_1__ tas_data; } ;
struct dsa_switch {struct sja1105_private* priv; } ;

/* Variables and functions */
 int SJA1105_NUM_PORTS ; 
 int /*<<< orphan*/  taprio_offload_free (struct tc_taprio_qopt_offload*) ; 

void sja1105_tas_teardown(struct dsa_switch *ds)
{
	struct sja1105_private *priv = ds->priv;
	struct tc_taprio_qopt_offload *offload;
	int port;

	for (port = 0; port < SJA1105_NUM_PORTS; port++) {
		offload = priv->tas_data.offload[port];
		if (!offload)
			continue;

		taprio_offload_free(offload);
	}
}
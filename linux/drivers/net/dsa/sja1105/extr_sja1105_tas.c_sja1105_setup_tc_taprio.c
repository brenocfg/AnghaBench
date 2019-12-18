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
struct tc_taprio_qopt_offload {int enable; scalar_t__ base_time; int num_entries; TYPE_1__* entries; scalar_t__ cycle_time_extension; } ;
struct sja1105_tas_data {int /*<<< orphan*/ ** offload; } ;
struct sja1105_private {TYPE_2__* ds; struct sja1105_tas_data tas_data; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct sja1105_private* priv; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ interval; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int ERANGE ; 
 int SJA1105_NUM_PORTS ; 
 scalar_t__ SJA1105_TAS_MAX_DELTA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ns_to_sja1105_delta (scalar_t__) ; 
 int sja1105_init_scheduling (struct sja1105_private*) ; 
 int sja1105_static_config_reload (struct sja1105_private*) ; 
 scalar_t__ sja1105_tas_check_conflicts (struct sja1105_private*,int,struct tc_taprio_qopt_offload*) ; 
 int /*<<< orphan*/  taprio_offload_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taprio_offload_get (struct tc_taprio_qopt_offload*) ; 

int sja1105_setup_tc_taprio(struct dsa_switch *ds, int port,
			    struct tc_taprio_qopt_offload *admin)
{
	struct sja1105_private *priv = ds->priv;
	struct sja1105_tas_data *tas_data = &priv->tas_data;
	int other_port, rc, i;

	/* Can't change an already configured port (must delete qdisc first).
	 * Can't delete the qdisc from an unconfigured port.
	 */
	if (!!tas_data->offload[port] == admin->enable)
		return -EINVAL;

	if (!admin->enable) {
		taprio_offload_free(tas_data->offload[port]);
		tas_data->offload[port] = NULL;

		rc = sja1105_init_scheduling(priv);
		if (rc < 0)
			return rc;

		return sja1105_static_config_reload(priv);
	}

	/* The cycle time extension is the amount of time the last cycle from
	 * the old OPER needs to be extended in order to phase-align with the
	 * base time of the ADMIN when that becomes the new OPER.
	 * But of course our switch needs to be reset to switch-over between
	 * the ADMIN and the OPER configs - so much for a seamless transition.
	 * So don't add insult over injury and just say we don't support cycle
	 * time extension.
	 */
	if (admin->cycle_time_extension)
		return -ENOTSUPP;

	if (!ns_to_sja1105_delta(admin->base_time)) {
		dev_err(ds->dev, "A base time of zero is not hardware-allowed\n");
		return -ERANGE;
	}

	for (i = 0; i < admin->num_entries; i++) {
		s64 delta_ns = admin->entries[i].interval;
		s64 delta_cycles = ns_to_sja1105_delta(delta_ns);
		bool too_long, too_short;

		too_long = (delta_cycles >= SJA1105_TAS_MAX_DELTA);
		too_short = (delta_cycles == 0);
		if (too_long || too_short) {
			dev_err(priv->ds->dev,
				"Interval %llu too %s for GCL entry %d\n",
				delta_ns, too_long ? "long" : "short", i);
			return -ERANGE;
		}
	}

	for (other_port = 0; other_port < SJA1105_NUM_PORTS; other_port++) {
		if (other_port == port)
			continue;

		if (sja1105_tas_check_conflicts(priv, other_port, admin))
			return -ERANGE;
	}

	tas_data->offload[port] = taprio_offload_get(admin);

	rc = sja1105_init_scheduling(priv);
	if (rc < 0)
		return rc;

	return sja1105_static_config_reload(priv);
}
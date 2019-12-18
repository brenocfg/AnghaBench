#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sja1105_table {scalar_t__ entries; scalar_t__ entry_count; TYPE_3__* ops; } ;
struct TYPE_8__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_2__ static_config; TYPE_1__* ports; TYPE_4__* ds; } ;
struct sja1105_general_params_entry {int hostprio; int incl_srcpt1; int send_meta1; int incl_srcpt0; int send_meta0; int casc_port; int /*<<< orphan*/  tpid2; int /*<<< orphan*/  tpid; int /*<<< orphan*/  ignore2stf; int /*<<< orphan*/  vlmask; int /*<<< orphan*/  vlmarker; int /*<<< orphan*/  vllupformat; int /*<<< orphan*/  mirr_port; int /*<<< orphan*/  host_port; int /*<<< orphan*/  mac_flt0; int /*<<< orphan*/  mac_fltres0; int /*<<< orphan*/  mac_flt1; int /*<<< orphan*/  mac_fltres1; int /*<<< orphan*/  switchid; int /*<<< orphan*/  mirr_ptacu; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; } ;
struct TYPE_9__ {int /*<<< orphan*/  unpacked_entry_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  mgmt_slot; } ;

/* Variables and functions */
 size_t BLK_IDX_GENERAL_PARAMS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_SJA1105 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SJA1105_LINKLOCAL_FILTER_A ; 
 int /*<<< orphan*/  SJA1105_LINKLOCAL_FILTER_A_MASK ; 
 int /*<<< orphan*/  SJA1105_LINKLOCAL_FILTER_B ; 
 int /*<<< orphan*/  SJA1105_LINKLOCAL_FILTER_B_MASK ; 
 scalar_t__ SJA1105_MAX_GENERAL_PARAMS_COUNT ; 
 int SJA1105_NUM_PORTS ; 
 scalar_t__ dsa_is_dsa_port (TYPE_4__*,int) ; 
 scalar_t__ dsa_is_user_port (TYPE_4__*,int) ; 
 int /*<<< orphan*/  dsa_upstream_port (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ kcalloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static int sja1105_init_general_params(struct sja1105_private *priv)
{
	struct sja1105_general_params_entry default_general_params = {
		/* Disallow dynamic changing of the mirror port */
		.mirr_ptacu = 0,
		.switchid = priv->ds->index,
		/* Priority queue for link-local management frames
		 * (both ingress to and egress from CPU - PTP, STP etc)
		 */
		.hostprio = 7,
		.mac_fltres1 = SJA1105_LINKLOCAL_FILTER_A,
		.mac_flt1    = SJA1105_LINKLOCAL_FILTER_A_MASK,
		.incl_srcpt1 = false,
		.send_meta1  = false,
		.mac_fltres0 = SJA1105_LINKLOCAL_FILTER_B,
		.mac_flt0    = SJA1105_LINKLOCAL_FILTER_B_MASK,
		.incl_srcpt0 = false,
		.send_meta0  = false,
		/* The destination for traffic matching mac_fltres1 and
		 * mac_fltres0 on all ports except host_port. Such traffic
		 * receieved on host_port itself would be dropped, except
		 * by installing a temporary 'management route'
		 */
		.host_port = dsa_upstream_port(priv->ds, 0),
		/* Same as host port */
		.mirr_port = dsa_upstream_port(priv->ds, 0),
		/* Link-local traffic received on casc_port will be forwarded
		 * to host_port without embedding the source port and device ID
		 * info in the destination MAC address (presumably because it
		 * is a cascaded port and a downstream SJA switch already did
		 * that). Default to an invalid port (to disable the feature)
		 * and overwrite this if we find any DSA (cascaded) ports.
		 */
		.casc_port = SJA1105_NUM_PORTS,
		/* No TTEthernet */
		.vllupformat = 0,
		.vlmarker = 0,
		.vlmask = 0,
		/* Only update correctionField for 1-step PTP (L2 transport) */
		.ignore2stf = 0,
		/* Forcefully disable VLAN filtering by telling
		 * the switch that VLAN has a different EtherType.
		 */
		.tpid = ETH_P_SJA1105,
		.tpid2 = ETH_P_SJA1105,
	};
	struct sja1105_table *table;
	int i, k = 0;

	for (i = 0; i < SJA1105_NUM_PORTS; i++) {
		if (dsa_is_dsa_port(priv->ds, i))
			default_general_params.casc_port = i;
		else if (dsa_is_user_port(priv->ds, i))
			priv->ports[i].mgmt_slot = k++;
	}

	table = &priv->static_config.tables[BLK_IDX_GENERAL_PARAMS];

	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	table->entries = kcalloc(SJA1105_MAX_GENERAL_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	if (!table->entries)
		return -ENOMEM;

	table->entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT;

	/* This table only has a single entry */
	((struct sja1105_general_params_entry *)table->entries)[0] =
				default_general_params;

	return 0;
}
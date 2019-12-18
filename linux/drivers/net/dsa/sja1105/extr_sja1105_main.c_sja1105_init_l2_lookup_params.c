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
typedef  int u64 ;
struct sja1105_table {scalar_t__ entries; scalar_t__ entry_count; TYPE_2__* ops; } ;
struct TYPE_3__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_1__ static_config; } ;
struct sja1105_l2_lookup_params_entry {int poly; int shared_learn; int no_enf_hostprt; int no_mgmt_learn; int use_static; int owr_dyn; int drpnolearn; int /*<<< orphan*/  maxaddrp; int /*<<< orphan*/  start_dynspc; int /*<<< orphan*/  dyn_tbsz; int /*<<< orphan*/  maxage; } ;
struct TYPE_4__ {int /*<<< orphan*/  unpacked_entry_size; } ;

/* Variables and functions */
 size_t BLK_IDX_L2_LOOKUP_PARAMS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SJA1105ET_FDB_BIN_SIZE ; 
 int /*<<< orphan*/  SJA1105_AGEING_TIME_MS (int) ; 
 int SJA1105_MAX_L2_LOOKUP_COUNT ; 
 scalar_t__ SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT ; 
 int SJA1105_NUM_PORTS ; 
 scalar_t__ kcalloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static int sja1105_init_l2_lookup_params(struct sja1105_private *priv)
{
	struct sja1105_table *table;
	u64 max_fdb_entries = SJA1105_MAX_L2_LOOKUP_COUNT / SJA1105_NUM_PORTS;
	struct sja1105_l2_lookup_params_entry default_l2_lookup_params = {
		/* Learned FDB entries are forgotten after 300 seconds */
		.maxage = SJA1105_AGEING_TIME_MS(300000),
		/* All entries within a FDB bin are available for learning */
		.dyn_tbsz = SJA1105ET_FDB_BIN_SIZE,
		/* And the P/Q/R/S equivalent setting: */
		.start_dynspc = 0,
		.maxaddrp = {max_fdb_entries, max_fdb_entries, max_fdb_entries,
			     max_fdb_entries, max_fdb_entries, },
		/* 2^8 + 2^5 + 2^3 + 2^2 + 2^1 + 1 in Koopman notation */
		.poly = 0x97,
		/* This selects between Independent VLAN Learning (IVL) and
		 * Shared VLAN Learning (SVL)
		 */
		.shared_learn = true,
		/* Don't discard management traffic based on ENFPORT -
		 * we don't perform SMAC port enforcement anyway, so
		 * what we are setting here doesn't matter.
		 */
		.no_enf_hostprt = false,
		/* Don't learn SMAC for mac_fltres1 and mac_fltres0.
		 * Maybe correlate with no_linklocal_learn from bridge driver?
		 */
		.no_mgmt_learn = true,
		/* P/Q/R/S only */
		.use_static = true,
		/* Dynamically learned FDB entries can overwrite other (older)
		 * dynamic FDB entries
		 */
		.owr_dyn = true,
		.drpnolearn = true,
	};

	table = &priv->static_config.tables[BLK_IDX_L2_LOOKUP_PARAMS];

	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	table->entries = kcalloc(SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	if (!table->entries)
		return -ENOMEM;

	table->entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT;

	/* This table only has a single entry */
	((struct sja1105_l2_lookup_params_entry *)table->entries)[0] =
				default_l2_lookup_params;

	return 0;
}
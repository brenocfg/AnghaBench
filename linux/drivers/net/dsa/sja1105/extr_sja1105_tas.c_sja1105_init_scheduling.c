#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tc_taprio_qopt_offload {int num_entries; TYPE_3__* entries; } ;
struct sja1105_tas_data {struct tc_taprio_qopt_offload** offload; } ;
struct sja1105_table {int entry_count; struct sja1105_schedule_params_entry* entries; TYPE_2__* ops; } ;
struct sja1105_schedule_params_entry {int actsubsch; int subschindx; int delta; int address; int* subscheind; int resmedia_en; int resmedia; int /*<<< orphan*/  destports; int /*<<< orphan*/  clksrc; } ;
struct sja1105_schedule_entry_points_params_entry {int actsubsch; int subschindx; int delta; int address; int* subscheind; int resmedia_en; int resmedia; int /*<<< orphan*/  destports; int /*<<< orphan*/  clksrc; } ;
struct sja1105_schedule_entry_points_entry {int actsubsch; int subschindx; int delta; int address; int* subscheind; int resmedia_en; int resmedia; int /*<<< orphan*/  destports; int /*<<< orphan*/  clksrc; } ;
struct sja1105_schedule_entry {int actsubsch; int subschindx; int delta; int address; int* subscheind; int resmedia_en; int resmedia; int /*<<< orphan*/  destports; int /*<<< orphan*/  clksrc; } ;
struct TYPE_4__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_1__ static_config; struct sja1105_tas_data tas_data; } ;
typedef  int s64 ;
struct TYPE_6__ {int interval; int gate_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  unpacked_entry_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 size_t BLK_IDX_SCHEDULE ; 
 size_t BLK_IDX_SCHEDULE_ENTRY_POINTS ; 
 size_t BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS ; 
 size_t BLK_IDX_SCHEDULE_PARAMS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SJA1105_GATE_MASK ; 
 int SJA1105_MAX_SCHEDULE_ENTRY_POINTS_PARAMS_COUNT ; 
 int SJA1105_MAX_SCHEDULE_PARAMS_COUNT ; 
 int SJA1105_NUM_PORTS ; 
 int /*<<< orphan*/  SJA1105_TAS_CLKSRC_STANDALONE ; 
 void* kcalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sja1105_schedule_params_entry*) ; 
 int ns_to_sja1105_delta (int) ; 

__attribute__((used)) static int sja1105_init_scheduling(struct sja1105_private *priv)
{
	struct sja1105_schedule_entry_points_entry *schedule_entry_points;
	struct sja1105_schedule_entry_points_params_entry
					*schedule_entry_points_params;
	struct sja1105_schedule_params_entry *schedule_params;
	struct sja1105_tas_data *tas_data = &priv->tas_data;
	struct sja1105_schedule_entry *schedule;
	struct sja1105_table *table;
	int schedule_start_idx;
	s64 entry_point_delta;
	int schedule_end_idx;
	int num_entries = 0;
	int num_cycles = 0;
	int cycle = 0;
	int i, k = 0;
	int port;

	/* Discard previous Schedule Table */
	table = &priv->static_config.tables[BLK_IDX_SCHEDULE];
	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	/* Discard previous Schedule Entry Points Parameters Table */
	table = &priv->static_config.tables[BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS];
	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	/* Discard previous Schedule Parameters Table */
	table = &priv->static_config.tables[BLK_IDX_SCHEDULE_PARAMS];
	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	/* Discard previous Schedule Entry Points Table */
	table = &priv->static_config.tables[BLK_IDX_SCHEDULE_ENTRY_POINTS];
	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	/* Figure out the dimensioning of the problem */
	for (port = 0; port < SJA1105_NUM_PORTS; port++) {
		if (tas_data->offload[port]) {
			num_entries += tas_data->offload[port]->num_entries;
			num_cycles++;
		}
	}

	/* Nothing to do */
	if (!num_cycles)
		return 0;

	/* Pre-allocate space in the static config tables */

	/* Schedule Table */
	table = &priv->static_config.tables[BLK_IDX_SCHEDULE];
	table->entries = kcalloc(num_entries, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	if (!table->entries)
		return -ENOMEM;
	table->entry_count = num_entries;
	schedule = table->entries;

	/* Schedule Points Parameters Table */
	table = &priv->static_config.tables[BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS];
	table->entries = kcalloc(SJA1105_MAX_SCHEDULE_ENTRY_POINTS_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	if (!table->entries)
		/* Previously allocated memory will be freed automatically in
		 * sja1105_static_config_free. This is true for all early
		 * returns below.
		 */
		return -ENOMEM;
	table->entry_count = SJA1105_MAX_SCHEDULE_ENTRY_POINTS_PARAMS_COUNT;
	schedule_entry_points_params = table->entries;

	/* Schedule Parameters Table */
	table = &priv->static_config.tables[BLK_IDX_SCHEDULE_PARAMS];
	table->entries = kcalloc(SJA1105_MAX_SCHEDULE_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	if (!table->entries)
		return -ENOMEM;
	table->entry_count = SJA1105_MAX_SCHEDULE_PARAMS_COUNT;
	schedule_params = table->entries;

	/* Schedule Entry Points Table */
	table = &priv->static_config.tables[BLK_IDX_SCHEDULE_ENTRY_POINTS];
	table->entries = kcalloc(num_cycles, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	if (!table->entries)
		return -ENOMEM;
	table->entry_count = num_cycles;
	schedule_entry_points = table->entries;

	/* Finally start populating the static config tables */
	schedule_entry_points_params->clksrc = SJA1105_TAS_CLKSRC_STANDALONE;
	schedule_entry_points_params->actsubsch = num_cycles - 1;

	for (port = 0; port < SJA1105_NUM_PORTS; port++) {
		const struct tc_taprio_qopt_offload *offload;

		offload = tas_data->offload[port];
		if (!offload)
			continue;

		schedule_start_idx = k;
		schedule_end_idx = k + offload->num_entries - 1;
		/* TODO this is the base time for the port's subschedule,
		 * relative to PTPSCHTM. But as we're using the standalone
		 * clock source and not PTP clock as time reference, there's
		 * little point in even trying to put more logic into this,
		 * like preserving the phases between the subschedules of
		 * different ports. We'll get all of that when switching to the
		 * PTP clock source.
		 */
		entry_point_delta = 1;

		schedule_entry_points[cycle].subschindx = cycle;
		schedule_entry_points[cycle].delta = entry_point_delta;
		schedule_entry_points[cycle].address = schedule_start_idx;

		/* The subschedule end indices need to be
		 * monotonically increasing.
		 */
		for (i = cycle; i < 8; i++)
			schedule_params->subscheind[i] = schedule_end_idx;

		for (i = 0; i < offload->num_entries; i++, k++) {
			s64 delta_ns = offload->entries[i].interval;

			schedule[k].delta = ns_to_sja1105_delta(delta_ns);
			schedule[k].destports = BIT(port);
			schedule[k].resmedia_en = true;
			schedule[k].resmedia = SJA1105_GATE_MASK &
					~offload->entries[i].gate_mask;
		}
		cycle++;
	}

	return 0;
}
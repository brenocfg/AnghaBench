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
struct sja1105_table {struct sja1105_l2_forwarding_params_entry* entries; } ;
struct sja1105_l2_forwarding_params_entry {scalar_t__* part_spc; } ;
typedef  int /*<<< orphan*/  sja1105_config_valid_t ;

/* Variables and functions */
 size_t BLK_IDX_L2_FORWARDING_PARAMS ; 
 int /*<<< orphan*/  SJA1105_CONFIG_OK ; 
 int SJA1105_MAX_FRAME_MEMORY ; 
 int /*<<< orphan*/  SJA1105_OVERCOMMITTED_FRAME_MEMORY ; 

__attribute__((used)) static sja1105_config_valid_t
static_config_check_memory_size(const struct sja1105_table *tables)
{
	const struct sja1105_l2_forwarding_params_entry *l2_fwd_params;
	int i, mem = 0;

	l2_fwd_params = tables[BLK_IDX_L2_FORWARDING_PARAMS].entries;

	for (i = 0; i < 8; i++)
		mem += l2_fwd_params->part_spc[i];

	if (mem > SJA1105_MAX_FRAME_MEMORY)
		return SJA1105_OVERCOMMITTED_FRAME_MEMORY;

	return SJA1105_CONFIG_OK;
}
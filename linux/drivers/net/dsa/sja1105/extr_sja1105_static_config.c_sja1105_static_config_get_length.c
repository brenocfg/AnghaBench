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
struct sja1105_table {int entry_count; TYPE_1__* ops; } ;
struct sja1105_static_config {struct sja1105_table* tables; } ;
typedef  enum sja1105_blk_idx { ____Placeholder_sja1105_blk_idx } sja1105_blk_idx ;
struct TYPE_2__ {unsigned int packed_entry_size; } ;

/* Variables and functions */
 int BLK_IDX_MAX ; 
 unsigned int SJA1105_SIZE_DEVICE_ID ; 
 int SJA1105_SIZE_TABLE_HEADER ; 

size_t
sja1105_static_config_get_length(const struct sja1105_static_config *config)
{
	unsigned int sum;
	unsigned int header_count;
	enum sja1105_blk_idx i;

	/* Ending header */
	header_count = 1;
	sum = SJA1105_SIZE_DEVICE_ID;

	/* Tables (headers and entries) */
	for (i = 0; i < BLK_IDX_MAX; i++) {
		const struct sja1105_table *table;

		table = &config->tables[i];
		if (table->entry_count)
			header_count++;

		sum += table->ops->packed_entry_size * table->entry_count;
	}
	/* Headers have an additional CRC at the end */
	sum += header_count * (SJA1105_SIZE_TABLE_HEADER + 4);
	/* Last header does not have an extra CRC because there is no data */
	sum -= 4;

	return sum;
}
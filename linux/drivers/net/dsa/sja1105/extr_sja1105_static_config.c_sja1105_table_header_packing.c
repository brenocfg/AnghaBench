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
struct sja1105_table_header {int /*<<< orphan*/  crc; int /*<<< orphan*/  len; int /*<<< orphan*/  block_id; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 size_t SJA1105_SIZE_TABLE_HEADER ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,size_t const,int) ; 

size_t sja1105_table_header_packing(void *buf, void *entry_ptr,
				    enum packing_op op)
{
	const size_t size = SJA1105_SIZE_TABLE_HEADER;
	struct sja1105_table_header *entry = entry_ptr;

	sja1105_packing(buf, &entry->block_id, 31, 24, size, op);
	sja1105_packing(buf, &entry->len,      55, 32, size, op);
	sja1105_packing(buf, &entry->crc,      95, 64, size, op);
	return size;
}
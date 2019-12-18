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
struct sja1105_schedule_params_entry {int /*<<< orphan*/ * subscheind; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 size_t SJA1105_SIZE_SCHEDULE_PARAMS_ENTRY ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,scalar_t__,size_t const,int) ; 

__attribute__((used)) static size_t sja1105_schedule_params_entry_packing(void *buf, void *entry_ptr,
						    enum packing_op op)
{
	const size_t size = SJA1105_SIZE_SCHEDULE_PARAMS_ENTRY;
	struct sja1105_schedule_params_entry *entry = entry_ptr;
	int offset, i;

	for (i = 0, offset = 16; i < 8; i++, offset += 10)
		sja1105_packing(buf, &entry->subscheind[i],
				offset + 9, offset + 0, size, op);
	return size;
}
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
struct sja1105_l2_forwarding_entry {int /*<<< orphan*/ * vlan_pmap; int /*<<< orphan*/  fl_domain; int /*<<< orphan*/  reach_port; int /*<<< orphan*/  bc_domain; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 size_t SJA1105_SIZE_L2_FORWARDING_ENTRY ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,size_t const,int) ; 

size_t sja1105_l2_forwarding_entry_packing(void *buf, void *entry_ptr,
					   enum packing_op op)
{
	const size_t size = SJA1105_SIZE_L2_FORWARDING_ENTRY;
	struct sja1105_l2_forwarding_entry *entry = entry_ptr;
	int offset, i;

	sja1105_packing(buf, &entry->bc_domain,  63, 59, size, op);
	sja1105_packing(buf, &entry->reach_port, 58, 54, size, op);
	sja1105_packing(buf, &entry->fl_domain,  53, 49, size, op);
	for (i = 0, offset = 25; i < 8; i++, offset += 3)
		sja1105_packing(buf, &entry->vlan_pmap[i],
				offset + 2, offset + 0, size, op);
	return size;
}
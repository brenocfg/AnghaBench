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
struct sja1105_l2_lookup_entry {int /*<<< orphan*/  index; int /*<<< orphan*/  enfport; int /*<<< orphan*/  destports; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  vlanid; int /*<<< orphan*/  iotag; int /*<<< orphan*/  mask_macaddr; int /*<<< orphan*/  mask_vlanid; int /*<<< orphan*/  mask_iotag; int /*<<< orphan*/  age; int /*<<< orphan*/  touched; int /*<<< orphan*/  retag; int /*<<< orphan*/  mirr; int /*<<< orphan*/  takets; int /*<<< orphan*/  mirrvlan; int /*<<< orphan*/  tsreg; scalar_t__ lockeds; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 size_t SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,size_t const,int) ; 

size_t sja1105pqrs_l2_lookup_entry_packing(void *buf, void *entry_ptr,
					   enum packing_op op)
{
	const size_t size = SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY;
	struct sja1105_l2_lookup_entry *entry = entry_ptr;

	if (entry->lockeds) {
		sja1105_packing(buf, &entry->tsreg,    159, 159, size, op);
		sja1105_packing(buf, &entry->mirrvlan, 158, 147, size, op);
		sja1105_packing(buf, &entry->takets,   146, 146, size, op);
		sja1105_packing(buf, &entry->mirr,     145, 145, size, op);
		sja1105_packing(buf, &entry->retag,    144, 144, size, op);
	} else {
		sja1105_packing(buf, &entry->touched,  159, 159, size, op);
		sja1105_packing(buf, &entry->age,      158, 144, size, op);
	}
	sja1105_packing(buf, &entry->mask_iotag,   143, 143, size, op);
	sja1105_packing(buf, &entry->mask_vlanid,  142, 131, size, op);
	sja1105_packing(buf, &entry->mask_macaddr, 130,  83, size, op);
	sja1105_packing(buf, &entry->iotag,         82,  82, size, op);
	sja1105_packing(buf, &entry->vlanid,        81,  70, size, op);
	sja1105_packing(buf, &entry->macaddr,       69,  22, size, op);
	sja1105_packing(buf, &entry->destports,     21,  17, size, op);
	sja1105_packing(buf, &entry->enfport,       16,  16, size, op);
	sja1105_packing(buf, &entry->index,         15,   6, size, op);
	return size;
}
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
struct sja1105_mgmt_entry {int /*<<< orphan*/  enfport; int /*<<< orphan*/  destports; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  takets; int /*<<< orphan*/  tsreg; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 size_t SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,size_t const,int) ; 

__attribute__((used)) static size_t sja1105pqrs_mgmt_route_entry_packing(void *buf, void *entry_ptr,
						   enum packing_op op)
{
	const size_t size = SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY;
	struct sja1105_mgmt_entry *entry = entry_ptr;

	/* In P/Q/R/S, enfport got renamed to mgmtvalid, but its purpose
	 * is the same (driver uses it to confirm that frame was sent).
	 * So just keep the name from E/T.
	 */
	sja1105_packing(buf, &entry->tsreg,     71, 71, size, op);
	sja1105_packing(buf, &entry->takets,    70, 70, size, op);
	sja1105_packing(buf, &entry->macaddr,   69, 22, size, op);
	sja1105_packing(buf, &entry->destports, 21, 17, size, op);
	sja1105_packing(buf, &entry->enfport,   16, 16, size, op);
	return size;
}
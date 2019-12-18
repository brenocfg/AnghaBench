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
typedef  int /*<<< orphan*/  u8 ;
struct sja1105_l2_lookup_entry {int /*<<< orphan*/  lockeds; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY ; 
 int SJA1105_SIZE_DYN_CMD ; 
 int /*<<< orphan*/  sja1105_packing (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int const,int) ; 
 size_t sja1105pqrs_l2_lookup_entry_packing (void*,void*,int) ; 

__attribute__((used)) static size_t
sja1105pqrs_dyn_l2_lookup_entry_packing(void *buf, void *entry_ptr,
					enum packing_op op)
{
	struct sja1105_l2_lookup_entry *entry = entry_ptr;
	u8 *cmd = buf + SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY;
	const int size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(cmd, &entry->lockeds, 28, 28, size, op);

	return sja1105pqrs_l2_lookup_entry_packing(buf, entry_ptr, op);
}
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
struct sja1105_l2_lookup_params_entry {int /*<<< orphan*/  no_mgmt_learn; int /*<<< orphan*/  no_enf_hostprt; int /*<<< orphan*/  shared_learn; int /*<<< orphan*/  poly; int /*<<< orphan*/  dyn_tbsz; int /*<<< orphan*/  maxage; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 size_t SJA1105ET_SIZE_L2_LOOKUP_PARAMS_ENTRY ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,size_t const,int) ; 

__attribute__((used)) static size_t
sja1105et_l2_lookup_params_entry_packing(void *buf, void *entry_ptr,
					 enum packing_op op)
{
	const size_t size = SJA1105ET_SIZE_L2_LOOKUP_PARAMS_ENTRY;
	struct sja1105_l2_lookup_params_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->maxage,         31, 17, size, op);
	sja1105_packing(buf, &entry->dyn_tbsz,       16, 14, size, op);
	sja1105_packing(buf, &entry->poly,           13,  6, size, op);
	sja1105_packing(buf, &entry->shared_learn,    5,  5, size, op);
	sja1105_packing(buf, &entry->no_enf_hostprt,  4,  4, size, op);
	sja1105_packing(buf, &entry->no_mgmt_learn,   3,  3, size, op);
	return size;
}
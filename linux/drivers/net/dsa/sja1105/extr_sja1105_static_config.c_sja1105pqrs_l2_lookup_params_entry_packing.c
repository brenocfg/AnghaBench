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
struct sja1105_l2_lookup_params_entry {int /*<<< orphan*/  learn_once; int /*<<< orphan*/  owr_dyn; int /*<<< orphan*/  use_static; int /*<<< orphan*/  no_mgmt_learn; int /*<<< orphan*/  no_enf_hostprt; int /*<<< orphan*/  shared_learn; int /*<<< orphan*/  drpnolearn; int /*<<< orphan*/  start_dynspc; int /*<<< orphan*/  maxage; int /*<<< orphan*/ * maxaddrp; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 size_t SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,size_t const,int) ; 

__attribute__((used)) static size_t
sja1105pqrs_l2_lookup_params_entry_packing(void *buf, void *entry_ptr,
					   enum packing_op op)
{
	const size_t size = SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY;
	struct sja1105_l2_lookup_params_entry *entry = entry_ptr;
	int offset, i;

	for (i = 0, offset = 58; i < 5; i++, offset += 11)
		sja1105_packing(buf, &entry->maxaddrp[i],
				offset + 10, offset + 0, size, op);
	sja1105_packing(buf, &entry->maxage,         57,  43, size, op);
	sja1105_packing(buf, &entry->start_dynspc,   42,  33, size, op);
	sja1105_packing(buf, &entry->drpnolearn,     32,  28, size, op);
	sja1105_packing(buf, &entry->shared_learn,   27,  27, size, op);
	sja1105_packing(buf, &entry->no_enf_hostprt, 26,  26, size, op);
	sja1105_packing(buf, &entry->no_mgmt_learn,  25,  25, size, op);
	sja1105_packing(buf, &entry->use_static,     24,  24, size, op);
	sja1105_packing(buf, &entry->owr_dyn,        23,  23, size, op);
	sja1105_packing(buf, &entry->learn_once,     22,  22, size, op);
	return size;
}
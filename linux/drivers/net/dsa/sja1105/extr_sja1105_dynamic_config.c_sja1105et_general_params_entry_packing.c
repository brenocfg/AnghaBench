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
struct sja1105_general_params_entry {int /*<<< orphan*/  mirr_port; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int SJA1105ET_SIZE_GENERAL_PARAMS_DYN_CMD ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int const,int) ; 

__attribute__((used)) static size_t
sja1105et_general_params_entry_packing(void *buf, void *entry_ptr,
				       enum packing_op op)
{
	struct sja1105_general_params_entry *entry = entry_ptr;
	const int size = SJA1105ET_SIZE_GENERAL_PARAMS_DYN_CMD;

	sja1105_packing(buf, &entry->mirr_port, 2, 0, size, op);
	/* Bogus return value, not used anywhere */
	return 0;
}
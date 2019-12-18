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
struct sja1105_dyn_cmd {int /*<<< orphan*/  errors; int /*<<< orphan*/  valid; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int SJA1105ET_SIZE_GENERAL_PARAMS_DYN_CMD ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,int const,int) ; 

__attribute__((used)) static void
sja1105et_general_params_cmd_packing(void *buf, struct sja1105_dyn_cmd *cmd,
				     enum packing_op op)
{
	const int size = SJA1105ET_SIZE_GENERAL_PARAMS_DYN_CMD;

	sja1105_packing(buf, &cmd->valid,  31, 31, size, op);
	sja1105_packing(buf, &cmd->errors, 30, 30, size, op);
}
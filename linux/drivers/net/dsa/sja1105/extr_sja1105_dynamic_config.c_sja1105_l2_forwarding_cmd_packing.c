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
struct sja1105_dyn_cmd {int /*<<< orphan*/  index; int /*<<< orphan*/  rdwrset; int /*<<< orphan*/  errors; int /*<<< orphan*/  valid; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int SJA1105_SIZE_DYN_CMD ; 
 int SJA1105_SIZE_L2_FORWARDING_ENTRY ; 
 int /*<<< orphan*/  sja1105_packing (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int const,int) ; 

__attribute__((used)) static void
sja1105_l2_forwarding_cmd_packing(void *buf, struct sja1105_dyn_cmd *cmd,
				  enum packing_op op)
{
	u8 *p = buf + SJA1105_SIZE_L2_FORWARDING_ENTRY;
	const int size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,   31, 31, size, op);
	sja1105_packing(p, &cmd->errors,  30, 30, size, op);
	sja1105_packing(p, &cmd->rdwrset, 29, 29, size, op);
	sja1105_packing(p, &cmd->index,    4,  0, size, op);
}
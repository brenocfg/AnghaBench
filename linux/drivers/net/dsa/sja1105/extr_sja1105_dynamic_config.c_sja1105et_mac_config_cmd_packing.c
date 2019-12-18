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
struct sja1105_dyn_cmd {int /*<<< orphan*/  index; int /*<<< orphan*/  valid; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int SJA1105_SIZE_DYN_CMD ; 
 int /*<<< orphan*/  sja1105_packing (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int const,int) ; 

__attribute__((used)) static void
sja1105et_mac_config_cmd_packing(void *buf, struct sja1105_dyn_cmd *cmd,
				 enum packing_op op)
{
	const int size = SJA1105_SIZE_DYN_CMD;
	/* Yup, user manual definitions are reversed */
	u8 *reg1 = buf + 4;

	sja1105_packing(reg1, &cmd->valid, 31, 31, size, op);
	sja1105_packing(reg1, &cmd->index, 26, 24, size, op);
}
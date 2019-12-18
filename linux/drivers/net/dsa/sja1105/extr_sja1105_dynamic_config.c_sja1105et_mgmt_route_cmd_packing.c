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
typedef  int u64 ;
struct sja1105_dyn_cmd {int dummy; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int PACK ; 
 int SJA1105ET_SIZE_L2_LOOKUP_ENTRY ; 
 int /*<<< orphan*/  SJA1105_SIZE_DYN_CMD ; 
 int /*<<< orphan*/  sja1105_pack (int /*<<< orphan*/ *,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sja1105et_l2_lookup_cmd_packing (void*,struct sja1105_dyn_cmd*,int) ; 

__attribute__((used)) static void
sja1105et_mgmt_route_cmd_packing(void *buf, struct sja1105_dyn_cmd *cmd,
				 enum packing_op op)
{
	u8 *p = buf + SJA1105ET_SIZE_L2_LOOKUP_ENTRY;
	u64 mgmtroute = 1;

	sja1105et_l2_lookup_cmd_packing(buf, cmd, op);
	if (op == PACK)
		sja1105_pack(p, &mgmtroute, 26, 26, SJA1105_SIZE_DYN_CMD);
}
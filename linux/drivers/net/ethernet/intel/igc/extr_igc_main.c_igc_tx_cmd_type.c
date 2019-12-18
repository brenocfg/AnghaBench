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
typedef  int u32 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int IGC_ADVTXD_DCMD_DEXT ; 
 int IGC_ADVTXD_DCMD_IFCS ; 
 int IGC_ADVTXD_DTYP_DATA ; 

__attribute__((used)) static u32 igc_tx_cmd_type(struct sk_buff *skb, u32 tx_flags)
{
	/* set type for advanced descriptor with frame checksum insertion */
	u32 cmd_type = IGC_ADVTXD_DTYP_DATA |
		       IGC_ADVTXD_DCMD_DEXT |
		       IGC_ADVTXD_DCMD_IFCS;

	return cmd_type;
}
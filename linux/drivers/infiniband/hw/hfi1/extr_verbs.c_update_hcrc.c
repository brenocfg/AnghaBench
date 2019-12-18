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
typedef  int u8 ;
typedef  int u64 ;

/* Variables and functions */
 int IB_OPCODE_TID_RDMA ; 
 scalar_t__ PBC_IHCRC_LKDETH ; 
 int PBC_INSERT_HCRC_SHIFT ; 
 int PBC_INSERT_HCRC_SMASK ; 

__attribute__((used)) static u64 update_hcrc(u8 opcode, u64 pbc)
{
	if ((opcode & IB_OPCODE_TID_RDMA) == IB_OPCODE_TID_RDMA) {
		pbc &= ~PBC_INSERT_HCRC_SMASK;
		pbc |= (u64)PBC_IHCRC_LKDETH << PBC_INSERT_HCRC_SHIFT;
	}
	return pbc;
}
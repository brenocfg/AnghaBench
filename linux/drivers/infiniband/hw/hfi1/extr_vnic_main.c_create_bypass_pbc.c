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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int PBC_CREDIT_RETURN ; 
 scalar_t__ PBC_IHCRC_NONE ; 
 int PBC_INSERT_BYPASS_ICRC ; 
 int PBC_INSERT_HCRC_SHIFT ; 
 int PBC_LENGTH_DWS_MASK ; 
 int PBC_LENGTH_DWS_SHIFT ; 
 int PBC_PACKET_BYPASS ; 
 int PBC_VL_MASK ; 
 int PBC_VL_SHIFT ; 

__attribute__((used)) static u64 create_bypass_pbc(u32 vl, u32 dw_len)
{
	u64 pbc;

	pbc = ((u64)PBC_IHCRC_NONE << PBC_INSERT_HCRC_SHIFT)
		| PBC_INSERT_BYPASS_ICRC | PBC_CREDIT_RETURN
		| PBC_PACKET_BYPASS
		| ((vl & PBC_VL_MASK) << PBC_VL_SHIFT)
		| (dw_len & PBC_LENGTH_DWS_MASK) << PBC_LENGTH_DWS_SHIFT;

	return pbc;
}
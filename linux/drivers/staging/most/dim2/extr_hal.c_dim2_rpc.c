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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ CDT ; 
 int CDT0_RPC_MASK ; 
 int CDT0_RPC_SHIFT ; 
 int dim2_read_ctr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 dim2_rpc(u8 ch_addr)
{
	u32 cdt0 = dim2_read_ctr(CDT + ch_addr, 0);

	return (cdt0 >> CDT0_RPC_SHIFT) & CDT0_RPC_MASK;
}
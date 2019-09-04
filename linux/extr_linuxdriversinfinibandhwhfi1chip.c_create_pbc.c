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
struct hfi1_pportdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ PBC_IHCRC_NONE ; 
 int PBC_INSERT_HCRC_SHIFT ; 
 int PBC_LENGTH_DWS_MASK ; 
 int PBC_LENGTH_DWS_SHIFT ; 
 int PBC_STATIC_RATE_CONTROL_COUNT_SHIFT ; 
 int PBC_VL_MASK ; 
 int PBC_VL_SHIFT ; 
 int delay_cycles (struct hfi1_pportdata*,int,int) ; 
 scalar_t__ unlikely (int) ; 

u64 create_pbc(struct hfi1_pportdata *ppd, u64 flags, int srate_mbs, u32 vl,
	       u32 dw_len)
{
	u64 pbc, delay = 0;

	if (unlikely(srate_mbs))
		delay = delay_cycles(ppd, srate_mbs, dw_len);

	pbc = flags
		| (delay << PBC_STATIC_RATE_CONTROL_COUNT_SHIFT)
		| ((u64)PBC_IHCRC_NONE << PBC_INSERT_HCRC_SHIFT)
		| (vl & PBC_VL_MASK) << PBC_VL_SHIFT
		| (dw_len & PBC_LENGTH_DWS_MASK)
			<< PBC_LENGTH_DWS_SHIFT;

	return pbc;
}
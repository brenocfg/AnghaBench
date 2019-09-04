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

/* Variables and functions */
 int I40E_HMC_L2OBJ_BASE_ALIGNMENT ; 

__attribute__((used)) static u64 i40e_align_l2obj_base(u64 offset)
{
	u64 aligned_offset = offset;

	if ((offset % I40E_HMC_L2OBJ_BASE_ALIGNMENT) > 0)
		aligned_offset += (I40E_HMC_L2OBJ_BASE_ALIGNMENT -
				   (offset % I40E_HMC_L2OBJ_BASE_ALIGNMENT));

	return aligned_offset;
}
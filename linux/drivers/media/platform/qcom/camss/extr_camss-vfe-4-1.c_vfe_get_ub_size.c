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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSM_VFE_VFE0_UB_SIZE_RDI ; 

__attribute__((used)) static u16 vfe_get_ub_size(u8 vfe_id)
{
	if (vfe_id == 0)
		return MSM_VFE_VFE0_UB_SIZE_RDI;

	return 0;
}
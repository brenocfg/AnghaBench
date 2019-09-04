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
typedef  size_t u8 ;

/* Variables and functions */
 size_t DCBX_INVALID_COS ; 
 size_t DCBX_MAX_NUM_COS ; 

__attribute__((used)) static void bnx2x_ets_e3b0_sp_pri_to_cos_init(u8 *sp_pri_to_cos)
{
	u8 pri = 0;
	for (pri = 0; pri < DCBX_MAX_NUM_COS; pri++)
		sp_pri_to_cos[pri] = DCBX_INVALID_COS;
}
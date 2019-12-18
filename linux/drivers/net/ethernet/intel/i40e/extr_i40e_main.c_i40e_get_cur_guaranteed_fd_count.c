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
struct i40e_pf {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFQF_FDSTAT ; 
 int I40E_PFQF_FDSTAT_GUARANT_CNT_MASK ; 
 int rd32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u32 i40e_get_cur_guaranteed_fd_count(struct i40e_pf *pf)
{
	u32 val, fcnt_prog;

	val = rd32(&pf->hw, I40E_PFQF_FDSTAT);
	fcnt_prog = (val & I40E_PFQF_FDSTAT_GUARANT_CNT_MASK);
	return fcnt_prog;
}
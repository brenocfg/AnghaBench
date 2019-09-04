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
struct i40iw_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_GLPE_CPUSTATUS0 ; 
 int /*<<< orphan*/  I40E_GLPE_CPUSTATUS1 ; 
 int /*<<< orphan*/  I40E_GLPE_CPUSTATUS2 ; 
 int /*<<< orphan*/  I40E_GLPE_FWLDSTATUS ; 
 int /*<<< orphan*/  i40iw_pr_info (char*,int,int) ; 
 int i40iw_rd32 (struct i40iw_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_wr32 (struct i40iw_hw*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void i40iw_wait_pe_ready(struct i40iw_hw *hw)
{
	u32 statusfw;
	u32 statuscpu0;
	u32 statuscpu1;
	u32 statuscpu2;
	u32 retrycount = 0;

	do {
		statusfw = i40iw_rd32(hw, I40E_GLPE_FWLDSTATUS);
		i40iw_pr_info("[%04d] fm load status[x%04X]\n", __LINE__, statusfw);
		statuscpu0 = i40iw_rd32(hw, I40E_GLPE_CPUSTATUS0);
		i40iw_pr_info("[%04d] CSR_CQP status[x%04X]\n", __LINE__, statuscpu0);
		statuscpu1 = i40iw_rd32(hw, I40E_GLPE_CPUSTATUS1);
		i40iw_pr_info("[%04d] I40E_GLPE_CPUSTATUS1 status[x%04X]\n",
			      __LINE__, statuscpu1);
		statuscpu2 = i40iw_rd32(hw, I40E_GLPE_CPUSTATUS2);
		i40iw_pr_info("[%04d] I40E_GLPE_CPUSTATUS2 status[x%04X]\n",
			      __LINE__, statuscpu2);
		if ((statuscpu0 == 0x80) && (statuscpu1 == 0x80) && (statuscpu2 == 0x80))
			break;	/* SUCCESS */
		msleep(1000);
		retrycount++;
	} while (retrycount < 14);
	i40iw_wr32(hw, 0xb4040, 0x4C104C5);
}
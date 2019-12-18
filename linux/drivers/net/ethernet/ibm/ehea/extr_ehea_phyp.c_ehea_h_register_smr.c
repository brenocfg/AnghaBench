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
typedef  unsigned long long u64 ;
typedef  scalar_t__ u32 ;
struct ehea_mr {unsigned long handle; scalar_t__ lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_REGISTER_SMR ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 unsigned long long ehea_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,unsigned long long const,unsigned long long const,unsigned long long const,unsigned long long,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_register_smr(const u64 adapter_handle, const u64 orig_mr_handle,
			const u64 vaddr_in, const u32 access_ctrl, const u32 pd,
			struct ehea_mr *mr)
{
	u64 hret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	hret = ehea_plpar_hcall9(H_REGISTER_SMR,
				 outs,
				 adapter_handle	      ,		 /* R4 */
				 orig_mr_handle,		 /* R5 */
				 vaddr_in,			 /* R6 */
				 (((u64)access_ctrl) << 32ULL),	 /* R7 */
				 pd,				 /* R8 */
				 0, 0, 0, 0);			 /* R9-R12 */

	mr->handle = outs[0];
	mr->lkey = (u32)outs[2];

	return hret;
}
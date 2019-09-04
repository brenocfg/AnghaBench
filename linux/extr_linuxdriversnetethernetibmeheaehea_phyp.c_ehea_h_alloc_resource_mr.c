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

/* Variables and functions */
 int /*<<< orphan*/  H_ALLOC_HEA_RESOURCE ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 unsigned long long ehea_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,unsigned long long const,int,unsigned long long const,unsigned long long const,unsigned long long,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_alloc_resource_mr(const u64 adapter_handle, const u64 vaddr,
			     const u64 length, const u32 access_ctrl,
			     const u32 pd, u64 *mr_handle, u32 *lkey)
{
	u64 hret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	hret = ehea_plpar_hcall9(H_ALLOC_HEA_RESOURCE,
				 outs,
				 adapter_handle,		   /* R4 */
				 5,				   /* R5 */
				 vaddr,				   /* R6 */
				 length,			   /* R7 */
				 (((u64) access_ctrl) << 32ULL),   /* R8 */
				 pd,				   /* R9 */
				 0, 0, 0);			   /* R10-R12 */

	*mr_handle = outs[0];
	*lkey = (u32)outs[2];
	return hret;
}
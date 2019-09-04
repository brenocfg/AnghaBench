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
typedef  int u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_FIRST_VF_CID ; 
 int BNX2X_VF_CIDS ; 
 int ILT_PAGE_CIDS ; 
 scalar_t__ IS_SRIOV (struct bnx2x*) ; 
 int L2_ILT_LINES (struct bnx2x*) ; 

__attribute__((used)) static inline u16 bnx2x_cid_ilt_lines(struct bnx2x *bp)
{
	if (IS_SRIOV(bp))
		return (BNX2X_FIRST_VF_CID + BNX2X_VF_CIDS)/ILT_PAGE_CIDS;
	return L2_ILT_LINES(bp);
}
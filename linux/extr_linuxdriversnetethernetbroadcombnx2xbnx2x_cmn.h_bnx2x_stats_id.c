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
struct bnx2x_fastpath {scalar_t__ cl_id; struct bnx2x* bp; } ;
struct bnx2x {int pf_num; scalar_t__ cnic_base_cl_id; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int FP_SB_MAX_E1x ; 
 scalar_t__ IS_FCOE_FP (struct bnx2x_fastpath*) ; 

__attribute__((used)) static inline u8 bnx2x_stats_id(struct bnx2x_fastpath *fp)
{
	struct bnx2x *bp = fp->bp;
	if (!CHIP_IS_E1x(bp)) {
		/* there are special statistics counters for FCoE 136..140 */
		if (IS_FCOE_FP(fp))
			return bp->cnic_base_cl_id + (bp->pf_num >> 1);
		return fp->cl_id;
	}
	return fp->cl_id + BP_PORT(bp) * FP_SB_MAX_E1x;
}
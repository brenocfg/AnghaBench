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
typedef  scalar_t__ u16 ;
struct bnx2x_virtf {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNX2X_NR_VIRTFN (struct bnx2x*) ; 
 struct bnx2x_virtf* BP_VF (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_vf_idx_by_abs_fid (struct bnx2x*,scalar_t__) ; 

__attribute__((used)) static
struct bnx2x_virtf *bnx2x_vf_by_abs_fid(struct bnx2x *bp, u16 abs_vfid)
{
	u16 idx =  (u16)bnx2x_vf_idx_by_abs_fid(bp, abs_vfid);
	return (idx < BNX2X_NR_VIRTFN(bp)) ? BP_VF(bp, idx) : NULL;
}
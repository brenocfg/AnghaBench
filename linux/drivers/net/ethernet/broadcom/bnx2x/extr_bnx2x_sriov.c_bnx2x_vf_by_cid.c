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
struct bnx2x_virtf {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_MAX_NUM_OF_VFS ; 
 int BNX2X_VF_CID_WND ; 
 struct bnx2x_virtf* bnx2x_vf_by_abs_fid (struct bnx2x*,int) ; 

__attribute__((used)) static struct bnx2x_virtf *bnx2x_vf_by_cid(struct bnx2x *bp, int vf_cid)
{
	/* extract the vf from vf_cid - relies on the following:
	 * 1. vfid on cid reflects the true abs_vfid
	 * 2. The max number of VFs (per path) is 64
	 */
	int abs_vfid = (vf_cid >> BNX2X_VF_CID_WND) & (BNX2X_MAX_NUM_OF_VFS-1);
	return bnx2x_vf_by_abs_fid(bp, abs_vfid);
}
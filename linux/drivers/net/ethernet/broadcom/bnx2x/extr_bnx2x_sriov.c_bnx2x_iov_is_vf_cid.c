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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNX2X_FIRST_VF_CID ; 
 scalar_t__ BNX2X_VF_CIDS ; 

__attribute__((used)) static u8 bnx2x_iov_is_vf_cid(struct bnx2x *bp, u16 cid)
{
	return ((cid >= BNX2X_FIRST_VF_CID) &&
		((cid - BNX2X_FIRST_VF_CID) < BNX2X_VF_CIDS));
}
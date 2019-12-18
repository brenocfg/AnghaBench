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
 int /*<<< orphan*/  bnx2x_vf_mbx_resp_send_msg (struct bnx2x*,struct bnx2x_virtf*,int) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_resp_single_tlv (struct bnx2x*,struct bnx2x_virtf*) ; 

__attribute__((used)) static void bnx2x_vf_mbx_resp(struct bnx2x *bp,
			      struct bnx2x_virtf *vf,
			      int rc)
{
	bnx2x_vf_mbx_resp_single_tlv(bp, vf);
	bnx2x_vf_mbx_resp_send_msg(bp, vf, rc);
}
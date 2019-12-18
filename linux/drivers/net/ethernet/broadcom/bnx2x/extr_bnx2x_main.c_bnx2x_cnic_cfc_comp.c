#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int cid; int /*<<< orphan*/  error; } ;
struct TYPE_4__ {TYPE_1__ comp; } ;
struct cnic_ctl_info {TYPE_2__ data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  member_0; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_CTL_COMPLETION_CMD ; 
 int /*<<< orphan*/  bnx2x_cnic_ctl_send_bh (struct bnx2x*,struct cnic_ctl_info*) ; 
 int /*<<< orphan*/  bnx2x_cnic_sp_post (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_cnic_cfc_comp(struct bnx2x *bp, int cid, u8 err)
{
	struct cnic_ctl_info ctl = {0};

	/* first we tell CNIC and only then we count this as a completion */
	ctl.cmd = CNIC_CTL_COMPLETION_CMD;
	ctl.data.comp.cid = cid;
	ctl.data.comp.error = err;

	bnx2x_cnic_ctl_send_bh(bp, &ctl);
	bnx2x_cnic_sp_post(bp, 0);
}
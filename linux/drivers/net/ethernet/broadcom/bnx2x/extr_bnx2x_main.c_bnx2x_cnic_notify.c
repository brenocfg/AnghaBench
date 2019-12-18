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
struct cnic_ctl_info {int cmd; int /*<<< orphan*/  member_0; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int bnx2x_cnic_ctl_send (struct bnx2x*,struct cnic_ctl_info*) ; 

int bnx2x_cnic_notify(struct bnx2x *bp, int cmd)
{
	struct cnic_ctl_info ctl = {0};

	ctl.cmd = cmd;

	return bnx2x_cnic_ctl_send(bp, &ctl);
}
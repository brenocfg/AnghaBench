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
struct TYPE_3__ {int len; int /*<<< orphan*/  cmd; scalar_t__ resp_needed; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ s; scalar_t__ u64; } ;
struct octeon_mbox_cmd {int /*<<< orphan*/ * fn_arg; int /*<<< orphan*/ * fn; scalar_t__ recv_status; scalar_t__ recv_len; scalar_t__ q_no; TYPE_2__ msg; } ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_MBOX_REQUEST ; 
 int /*<<< orphan*/  OCTEON_VF_FLR_REQUEST ; 
 int /*<<< orphan*/  octeon_mbox_write (struct octeon_device*,struct octeon_mbox_cmd*) ; 

void cn23xx_vf_ask_pf_to_do_flr(struct octeon_device *oct)
{
	struct octeon_mbox_cmd mbox_cmd;

	mbox_cmd.msg.u64 = 0;
	mbox_cmd.msg.s.type = OCTEON_MBOX_REQUEST;
	mbox_cmd.msg.s.resp_needed = 0;
	mbox_cmd.msg.s.cmd = OCTEON_VF_FLR_REQUEST;
	mbox_cmd.msg.s.len = 1;
	mbox_cmd.q_no = 0;
	mbox_cmd.recv_len = 0;
	mbox_cmd.recv_status = 0;
	mbox_cmd.fn = NULL;
	mbox_cmd.fn_arg = NULL;

	octeon_mbox_write(oct, &mbox_cmd);
}
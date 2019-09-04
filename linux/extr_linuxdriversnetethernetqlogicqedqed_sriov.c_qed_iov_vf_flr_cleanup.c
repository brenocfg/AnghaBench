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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_2__* cdev; } ;
struct TYPE_4__ {TYPE_1__* p_iov_info; } ;
struct TYPE_3__ {scalar_t__ total_vfs; } ;

/* Variables and functions */
 int VF_MAX_STATIC ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qed_iov_execute_vf_flr_cleanup (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int /*<<< orphan*/ *) ; 
 int qed_mcp_ack_vf_flr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_iov_vf_flr_cleanup(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	u32 ack_vfs[VF_MAX_STATIC / 32];
	int rc = 0;
	u16 i;

	memset(ack_vfs, 0, sizeof(u32) * (VF_MAX_STATIC / 32));

	/* Since BRB <-> PRS interface can't be tested as part of the flr
	 * polling due to HW limitations, simply sleep a bit. And since
	 * there's no need to wait per-vf, do it before looping.
	 */
	msleep(100);

	for (i = 0; i < p_hwfn->cdev->p_iov_info->total_vfs; i++)
		qed_iov_execute_vf_flr_cleanup(p_hwfn, p_ptt, i, ack_vfs);

	rc = qed_mcp_ack_vf_flr(p_hwfn, p_ptt, ack_vfs);
	return rc;
}
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
typedef  int /*<<< orphan*/  u16 ;
struct qed_vf_info {int spoof_chk; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool qed_iov_spoofchk_get(struct qed_hwfn *p_hwfn, int vfid)
{
	struct qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	if (!vf_info)
		return false;

	return vf_info->spoof_chk;
}
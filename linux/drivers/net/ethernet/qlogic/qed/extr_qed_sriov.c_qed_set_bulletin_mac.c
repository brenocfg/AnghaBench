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
struct qed_public_vf_info {int /*<<< orphan*/  forced_mac; int /*<<< orphan*/  mac; scalar_t__ is_trusted_configured; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_iov_bulletin_set_forced_mac (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_iov_bulletin_set_mac (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qed_set_bulletin_mac(struct qed_hwfn *hwfn,
				 struct qed_public_vf_info *info,
				 int vfid)
{
	if (info->is_trusted_configured)
		qed_iov_bulletin_set_mac(hwfn, info->mac, vfid);
	else
		qed_iov_bulletin_set_forced_mac(hwfn, info->forced_mac, vfid);
}
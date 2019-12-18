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
typedef  int /*<<< orphan*/  u16 ;
struct qed_hwfn {TYPE_2__* vf_iov_info; } ;
struct pf_vf_pfdev_info {int /*<<< orphan*/  fw_eng; int /*<<< orphan*/  fw_rev; int /*<<< orphan*/  fw_minor; int /*<<< orphan*/  fw_major; } ;
struct TYPE_3__ {struct pf_vf_pfdev_info pfdev_info; } ;
struct TYPE_4__ {TYPE_1__ acquire_resp; } ;

/* Variables and functions */

void qed_vf_get_fw_version(struct qed_hwfn *p_hwfn,
			   u16 *fw_major, u16 *fw_minor,
			   u16 *fw_rev, u16 *fw_eng)
{
	struct pf_vf_pfdev_info *info;

	info = &p_hwfn->vf_iov_info->acquire_resp.pfdev_info;

	*fw_major = info->fw_major;
	*fw_minor = info->fw_minor;
	*fw_rev = info->fw_rev;
	*fw_eng = info->fw_eng;
}
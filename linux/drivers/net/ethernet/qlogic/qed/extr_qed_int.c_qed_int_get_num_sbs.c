#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qed_sb_cnt_info {int dummy; } ;
struct qed_igu_info {int /*<<< orphan*/  usage; } ;
struct TYPE_2__ {struct qed_igu_info* p_igu_info; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct qed_sb_cnt_info*,int /*<<< orphan*/ *,int) ; 

void qed_int_get_num_sbs(struct qed_hwfn	*p_hwfn,
			 struct qed_sb_cnt_info *p_sb_cnt_info)
{
	struct qed_igu_info *info = p_hwfn->hw_info.p_igu_info;

	if (!info || !p_sb_cnt_info)
		return;

	memcpy(p_sb_cnt_info, &info->usage, sizeof(*p_sb_cnt_info));
}
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
typedef  size_t u8 ;
struct qed_sb_sp_info {TYPE_1__* pi_info_arr; } ;
struct qed_hwfn {struct qed_sb_sp_info* p_sp_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cookie; int /*<<< orphan*/ * comp_cb; } ;

/* Variables and functions */
 int ENOMEM ; 

int qed_int_unregister_cb(struct qed_hwfn *p_hwfn, u8 pi)
{
	struct qed_sb_sp_info *p_sp_sb = p_hwfn->p_sp_sb;

	if (p_sp_sb->pi_info_arr[pi].comp_cb == NULL)
		return -ENOMEM;

	p_sp_sb->pi_info_arr[pi].comp_cb = NULL;
	p_sp_sb->pi_info_arr[pi].cookie = NULL;

	return 0;
}
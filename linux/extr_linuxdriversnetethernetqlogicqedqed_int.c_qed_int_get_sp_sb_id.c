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
struct qed_hwfn {TYPE_2__* p_sp_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  igu_sb_id; } ;
struct TYPE_4__ {TYPE_1__ sb_info; } ;

/* Variables and functions */

u16 qed_int_get_sp_sb_id(struct qed_hwfn *p_hwfn)
{
	return p_hwfn->p_sp_sb->sb_info.igu_sb_id;
}
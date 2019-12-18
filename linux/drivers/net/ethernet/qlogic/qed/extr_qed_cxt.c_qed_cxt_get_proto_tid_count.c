#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qed_hwfn {TYPE_3__* p_cxt_mngr; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
struct TYPE_6__ {TYPE_2__* conn_cfg; } ;
struct TYPE_5__ {TYPE_1__* tid_seg; } ;
struct TYPE_4__ {scalar_t__ count; } ;

/* Variables and functions */
 int TASK_SEGMENTS ; 

u32 qed_cxt_get_proto_tid_count(struct qed_hwfn *p_hwfn,
				enum protocol_type type)
{
	u32 cnt = 0;
	int i;

	for (i = 0; i < TASK_SEGMENTS; i++)
		cnt += p_hwfn->p_cxt_mngr->conn_cfg[type].tid_seg[i].count;

	return cnt;
}
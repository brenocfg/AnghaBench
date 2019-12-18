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
struct TYPE_2__ {int dorq_attn; } ;
struct qed_hwfn {TYPE_1__ db_recovery_info; } ;

/* Variables and functions */
 int qed_dorq_attn_int_sts (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_dorq_attn_overflow (struct qed_hwfn*) ; 

__attribute__((used)) static int qed_dorq_attn_cb(struct qed_hwfn *p_hwfn)
{
	p_hwfn->db_recovery_info.dorq_attn = true;
	qed_dorq_attn_overflow(p_hwfn);

	return qed_dorq_attn_int_sts(p_hwfn);
}
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
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void qed_init_fill(struct qed_hwfn *p_hwfn,
			  struct qed_ptt *p_ptt,
			  u32 addr, u32 fill, u32 fill_count)
{
	u32 i;

	for (i = 0; i < fill_count; i++, addr += sizeof(u32))
		qed_wr(p_hwfn, p_ptt, addr, fill);
}
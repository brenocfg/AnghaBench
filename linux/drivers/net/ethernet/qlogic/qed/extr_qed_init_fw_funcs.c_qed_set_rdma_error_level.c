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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ NUM_STORMS ; 
 int /*<<< orphan*/  qed_get_rdma_assert_ram_addr (struct qed_hwfn*,scalar_t__) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,scalar_t__) ; 

void qed_set_rdma_error_level(struct qed_hwfn *p_hwfn,
			      struct qed_ptt *p_ptt,
			      u8 assert_level[NUM_STORMS])
{
	u8 storm_id;

	for (storm_id = 0; storm_id < NUM_STORMS; storm_id++) {
		u32 ram_addr = qed_get_rdma_assert_ram_addr(p_hwfn, storm_id);

		qed_wr(p_hwfn, p_ptt, ram_addr, assert_level[storm_id]);
	}
}
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
struct qed_hwfn {int dummy; } ;
struct qed_bmap {scalar_t__ max_count; int /*<<< orphan*/  name; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int test_and_clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 

void qed_bmap_release_id(struct qed_hwfn *p_hwfn,
			 struct qed_bmap *bmap, u32 id_num)
{
	bool b_acquired;

	if (id_num >= bmap->max_count)
		return;

	b_acquired = test_and_clear_bit(id_num, bmap->bitmap);
	if (!b_acquired) {
		DP_NOTICE(p_hwfn, "%s bitmap: id %d already released\n",
			  bmap->name, id_num);
		return;
	}

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "%s bitmap: released id %d\n",
		   bmap->name, id_num);
}
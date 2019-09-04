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
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 

int qed_rdma_bmap_alloc_id(struct qed_hwfn *p_hwfn,
			   struct qed_bmap *bmap, u32 *id_num)
{
	*id_num = find_first_zero_bit(bmap->bitmap, bmap->max_count);
	if (*id_num >= bmap->max_count)
		return -EINVAL;

	__set_bit(*id_num, bmap->bitmap);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "%s bitmap: allocated id %d\n",
		   bmap->name, *id_num);

	return 0;
}
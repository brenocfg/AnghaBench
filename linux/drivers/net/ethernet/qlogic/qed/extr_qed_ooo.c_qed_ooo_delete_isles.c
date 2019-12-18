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
struct qed_ooo_isle {int /*<<< orphan*/  list_entry; int /*<<< orphan*/  buffers_list; } ;
struct qed_ooo_info {int /*<<< orphan*/  free_isles_list; int /*<<< orphan*/  cur_isles_number; int /*<<< orphan*/  free_buffers_list; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct qed_ooo_isle* qed_ooo_seek_isle (struct qed_hwfn*,struct qed_ooo_info*,int /*<<< orphan*/ ,scalar_t__) ; 

void qed_ooo_delete_isles(struct qed_hwfn *p_hwfn,
			  struct qed_ooo_info *p_ooo_info,
			  u32 cid, u8 drop_isle, u8 drop_size)
{
	struct qed_ooo_isle *p_isle = NULL;
	u8 isle_idx;

	for (isle_idx = 0; isle_idx < drop_size; isle_idx++) {
		p_isle = qed_ooo_seek_isle(p_hwfn, p_ooo_info, cid, drop_isle);
		if (!p_isle) {
			DP_NOTICE(p_hwfn,
				  "Isle %d is not found(cid %d)\n",
				  drop_isle, cid);
			return;
		}
		if (list_empty(&p_isle->buffers_list))
			DP_NOTICE(p_hwfn,
				  "Isle %d is empty(cid %d)\n", drop_isle, cid);
		else
			list_splice_tail_init(&p_isle->buffers_list,
					      &p_ooo_info->free_buffers_list);

		list_del(&p_isle->list_entry);
		p_ooo_info->cur_isles_number--;
		list_add(&p_isle->list_entry, &p_ooo_info->free_isles_list);
	}
}
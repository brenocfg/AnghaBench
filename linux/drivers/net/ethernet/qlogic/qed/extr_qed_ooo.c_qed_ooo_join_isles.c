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
struct qed_ooo_info {int /*<<< orphan*/  free_isles_list; int /*<<< orphan*/  ready_buffers_list; int /*<<< orphan*/  cur_isles_number; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct qed_ooo_isle* qed_ooo_seek_isle (struct qed_hwfn*,struct qed_ooo_info*,int /*<<< orphan*/ ,scalar_t__) ; 

void qed_ooo_join_isles(struct qed_hwfn *p_hwfn,
			struct qed_ooo_info *p_ooo_info, u32 cid, u8 left_isle)
{
	struct qed_ooo_isle *p_right_isle = NULL;
	struct qed_ooo_isle *p_left_isle = NULL;

	p_right_isle = qed_ooo_seek_isle(p_hwfn, p_ooo_info, cid,
					 left_isle + 1);
	if (!p_right_isle) {
		DP_NOTICE(p_hwfn,
			  "Right isle %d is not found(cid %d)\n",
			  left_isle + 1, cid);
		return;
	}

	list_del(&p_right_isle->list_entry);
	p_ooo_info->cur_isles_number--;
	if (left_isle) {
		p_left_isle = qed_ooo_seek_isle(p_hwfn, p_ooo_info, cid,
						left_isle);
		if (!p_left_isle) {
			DP_NOTICE(p_hwfn,
				  "Left isle %d is not found(cid %d)\n",
				  left_isle, cid);
			return;
		}
		list_splice_tail_init(&p_right_isle->buffers_list,
				      &p_left_isle->buffers_list);
	} else {
		list_splice_tail_init(&p_right_isle->buffers_list,
				      &p_ooo_info->ready_buffers_list);
	}
	list_add_tail(&p_right_isle->list_entry, &p_ooo_info->free_isles_list);
}
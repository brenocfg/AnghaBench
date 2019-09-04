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
struct qed_ooo_info {int /*<<< orphan*/  ready_buffers_list; } ;
struct qed_ooo_buffer {int /*<<< orphan*/  list_entry; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qed_ooo_put_ready_buffer(struct qed_hwfn *p_hwfn,
			      struct qed_ooo_info *p_ooo_info,
			      struct qed_ooo_buffer *p_buffer, u8 on_tail)
{
	if (on_tail)
		list_add_tail(&p_buffer->list_entry,
			      &p_ooo_info->ready_buffers_list);
	else
		list_add(&p_buffer->list_entry,
			 &p_ooo_info->ready_buffers_list);
}
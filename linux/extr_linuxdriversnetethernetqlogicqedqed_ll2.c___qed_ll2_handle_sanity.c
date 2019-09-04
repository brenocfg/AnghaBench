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
typedef  size_t u8 ;
struct qed_ll2_info {int /*<<< orphan*/  mutex; scalar_t__ b_active; } ;
struct qed_hwfn {struct qed_ll2_info* p_ll2_info; } ;

/* Variables and functions */
 size_t QED_MAX_NUM_OF_LL2_CONNECTIONS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qed_ll2_info *__qed_ll2_handle_sanity(struct qed_hwfn *p_hwfn,
						    u8 connection_handle,
						    bool b_lock,
						    bool b_only_active)
{
	struct qed_ll2_info *p_ll2_conn, *p_ret = NULL;

	if (connection_handle >= QED_MAX_NUM_OF_LL2_CONNECTIONS)
		return NULL;

	if (!p_hwfn->p_ll2_info)
		return NULL;

	p_ll2_conn = &p_hwfn->p_ll2_info[connection_handle];

	if (b_only_active) {
		if (b_lock)
			mutex_lock(&p_ll2_conn->mutex);
		if (p_ll2_conn->b_active)
			p_ret = p_ll2_conn;
		if (b_lock)
			mutex_unlock(&p_ll2_conn->mutex);
	} else {
		p_ret = p_ll2_conn;
	}

	return p_ret;
}
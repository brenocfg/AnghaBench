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
struct list_head {struct list_head* next; } ;
struct i40iw_sc_qp {struct list_head list; } ;

/* Variables and functions */
 struct i40iw_sc_qp* i40iw_qp_from_entry (struct list_head*) ; 
 scalar_t__ list_empty (struct list_head*) ; 

__attribute__((used)) static struct i40iw_sc_qp *i40iw_get_qp(struct list_head *head, struct i40iw_sc_qp *qp)
{
	struct list_head *entry = NULL;
	struct list_head *lastentry;

	if (list_empty(head))
		return NULL;

	if (!qp) {
		entry = head->next;
	} else {
		lastentry = &qp->list;
		entry = (lastentry != head) ? lastentry->next : NULL;
	}

	return i40iw_qp_from_entry(entry);
}
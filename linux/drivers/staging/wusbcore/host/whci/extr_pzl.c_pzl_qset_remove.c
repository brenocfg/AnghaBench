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
struct whc_qset {int in_hw_list; int in_sw_list; int /*<<< orphan*/  list_node; } ;
struct whc {int /*<<< orphan*/  periodic_removed_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pzl_qset_remove(struct whc *whc, struct whc_qset *qset)
{
	list_move(&qset->list_node, &whc->periodic_removed_list);
	qset->in_hw_list = false;
	qset->in_sw_list = false;
}
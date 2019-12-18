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
struct whc_qset {int /*<<< orphan*/  remove_complete; int /*<<< orphan*/  list_node; scalar_t__ remove; } ;
struct whc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

void qset_remove_complete(struct whc *whc, struct whc_qset *qset)
{
	qset->remove = 0;
	list_del_init(&qset->list_node);
	complete(&qset->remove_complete);
}
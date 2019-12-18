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
struct whc_qset {int remove; } ;
struct whc {int /*<<< orphan*/  periodic_work; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  qset_delete (struct whc*,struct whc_qset*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pzl_qset_delete(struct whc *whc, struct whc_qset *qset)
{
	qset->remove = 1;
	queue_work(whc->workqueue, &whc->periodic_work);
	qset_delete(whc, qset);
}
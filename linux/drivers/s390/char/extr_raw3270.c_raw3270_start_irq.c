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
struct raw3270_view {struct raw3270* dev; } ;
struct raw3270_request {int /*<<< orphan*/  list; struct raw3270_view* view; } ;
struct raw3270 {int /*<<< orphan*/  req_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw3270_get_view (struct raw3270_view*) ; 

int
raw3270_start_irq(struct raw3270_view *view, struct raw3270_request *rq)
{
	struct raw3270 *rp;

	rp = view->dev;
	rq->view = view;
	raw3270_get_view(view);
	list_add_tail(&rq->list, &rp->req_queue);
	return 0;
}
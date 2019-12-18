#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  cda; scalar_t__ count; scalar_t__ cmd_code; } ;
struct raw3270_request {scalar_t__ rc; scalar_t__ rescnt; TYPE_1__ ccw; int /*<<< orphan*/  buffer; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void
raw3270_request_reset(struct raw3270_request *rq)
{
	BUG_ON(!list_empty(&rq->list));
	rq->ccw.cmd_code = 0;
	rq->ccw.count = 0;
	rq->ccw.cda = __pa(rq->buffer);
	rq->ccw.flags = CCW_FLAG_SLI;
	rq->rescnt = 0;
	rq->rc = 0;
}
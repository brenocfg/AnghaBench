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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  cda; } ;
struct raw3270_request {size_t size; TYPE_1__ ccw; int /*<<< orphan*/  buffer; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct raw3270_request* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct raw3270_request*) ; 
 int /*<<< orphan*/  kmalloc (size_t,int) ; 
 struct raw3270_request* kzalloc (int,int) ; 

struct raw3270_request *
raw3270_request_alloc(size_t size)
{
	struct raw3270_request *rq;

	/* Allocate request structure */
	rq = kzalloc(sizeof(struct raw3270_request), GFP_KERNEL | GFP_DMA);
	if (!rq)
		return ERR_PTR(-ENOMEM);

	/* alloc output buffer. */
	if (size > 0) {
		rq->buffer = kmalloc(size, GFP_KERNEL | GFP_DMA);
		if (!rq->buffer) {
			kfree(rq);
			return ERR_PTR(-ENOMEM);
		}
	}
	rq->size = size;
	INIT_LIST_HEAD(&rq->list);

	/*
	 * Setup ccw.
	 */
	rq->ccw.cda = __pa(rq->buffer);
	rq->ccw.flags = CCW_FLAG_SLI;

	return rq;
}
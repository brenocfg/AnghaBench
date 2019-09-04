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
struct ib_device {struct ib_cq* (* create_cq ) (struct ib_device*,struct ib_cq_init_attr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct ib_cq_init_attr {int dummy; } ;
struct TYPE_2__ {char const* kern_name; int /*<<< orphan*/  type; } ;
struct ib_cq {void (* event_handler ) (struct ib_event*,void*) ;TYPE_1__ res; int /*<<< orphan*/  usecnt; void* cq_context; int /*<<< orphan*/  comp_handler; int /*<<< orphan*/ * uobject; struct ib_device* device; } ;
typedef  int /*<<< orphan*/  ib_comp_handler ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct ib_cq*) ; 
 int /*<<< orphan*/  RDMA_RESTRACK_CQ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_restrack_add (TYPE_1__*) ; 
 struct ib_cq* stub1 (struct ib_device*,struct ib_cq_init_attr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct ib_cq *__ib_create_cq(struct ib_device *device,
			     ib_comp_handler comp_handler,
			     void (*event_handler)(struct ib_event *, void *),
			     void *cq_context,
			     const struct ib_cq_init_attr *cq_attr,
			     const char *caller)
{
	struct ib_cq *cq;

	cq = device->create_cq(device, cq_attr, NULL, NULL);

	if (!IS_ERR(cq)) {
		cq->device        = device;
		cq->uobject       = NULL;
		cq->comp_handler  = comp_handler;
		cq->event_handler = event_handler;
		cq->cq_context    = cq_context;
		atomic_set(&cq->usecnt, 0);
		cq->res.type = RDMA_RESTRACK_CQ;
		cq->res.kern_name = caller;
		rdma_restrack_add(&cq->res);
	}

	return cq;
}
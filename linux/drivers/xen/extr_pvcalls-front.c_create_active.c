#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* in; } ;
struct TYPE_9__ {int irq; int /*<<< orphan*/  out_mutex; int /*<<< orphan*/  in_mutex; TYPE_2__* ring; void* ref; TYPE_1__ data; int /*<<< orphan*/  inflight_conn_req; } ;
struct sock_mapping {int active_socket; TYPE_3__ active; } ;
struct TYPE_10__ {int /*<<< orphan*/  otherend_id; } ;
struct TYPE_8__ {void** ref; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PVCALLS_RING_ORDER ; 
 int bind_evtchn_to_irqhandler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sock_mapping*) ; 
 void* gnttab_grant_foreign_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfn_to_gfn (scalar_t__) ; 
 int /*<<< orphan*/  pvcalls_front_conn_handler ; 
 TYPE_4__* pvcalls_front_dev ; 
 scalar_t__ virt_to_pfn (void*) ; 
 int xenbus_alloc_evtchn (TYPE_4__*,int*) ; 
 int /*<<< orphan*/  xenbus_free_evtchn (TYPE_4__*,int) ; 

__attribute__((used)) static int create_active(struct sock_mapping *map, int *evtchn)
{
	void *bytes;
	int ret = -ENOMEM, irq = -1, i;

	*evtchn = -1;
	init_waitqueue_head(&map->active.inflight_conn_req);

	bytes = map->active.data.in;
	for (i = 0; i < (1 << PVCALLS_RING_ORDER); i++)
		map->active.ring->ref[i] = gnttab_grant_foreign_access(
			pvcalls_front_dev->otherend_id,
			pfn_to_gfn(virt_to_pfn(bytes) + i), 0);

	map->active.ref = gnttab_grant_foreign_access(
		pvcalls_front_dev->otherend_id,
		pfn_to_gfn(virt_to_pfn((void *)map->active.ring)), 0);

	ret = xenbus_alloc_evtchn(pvcalls_front_dev, evtchn);
	if (ret)
		goto out_error;
	irq = bind_evtchn_to_irqhandler(*evtchn, pvcalls_front_conn_handler,
					0, "pvcalls-frontend", map);
	if (irq < 0) {
		ret = irq;
		goto out_error;
	}

	map->active.irq = irq;
	map->active_socket = true;
	mutex_init(&map->active.in_mutex);
	mutex_init(&map->active.out_mutex);

	return 0;

out_error:
	if (*evtchn >= 0)
		xenbus_free_evtchn(pvcalls_front_dev, *evtchn);
	return ret;
}
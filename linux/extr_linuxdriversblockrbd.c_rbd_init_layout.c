#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ stripe_unit; int stripe_count; scalar_t__ pool_id; int /*<<< orphan*/  pool_ns; void* object_size; } ;
struct TYPE_6__ {scalar_t__ stripe_unit; int stripe_count; scalar_t__ data_pool_id; } ;
struct rbd_device {TYPE_2__ layout; TYPE_3__ header; TYPE_1__* spec; } ;
struct TYPE_4__ {scalar_t__ pool_id; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOPOOL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* rbd_obj_bytes (TYPE_3__*) ; 

__attribute__((used)) static void rbd_init_layout(struct rbd_device *rbd_dev)
{
	if (rbd_dev->header.stripe_unit == 0 ||
	    rbd_dev->header.stripe_count == 0) {
		rbd_dev->header.stripe_unit = rbd_obj_bytes(&rbd_dev->header);
		rbd_dev->header.stripe_count = 1;
	}

	rbd_dev->layout.stripe_unit = rbd_dev->header.stripe_unit;
	rbd_dev->layout.stripe_count = rbd_dev->header.stripe_count;
	rbd_dev->layout.object_size = rbd_obj_bytes(&rbd_dev->header);
	rbd_dev->layout.pool_id = rbd_dev->header.data_pool_id == CEPH_NOPOOL ?
			  rbd_dev->spec->pool_id : rbd_dev->header.data_pool_id;
	RCU_INIT_POINTER(rbd_dev->layout.pool_ns, NULL);
}
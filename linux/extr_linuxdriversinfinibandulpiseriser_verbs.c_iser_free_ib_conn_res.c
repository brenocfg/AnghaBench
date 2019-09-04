#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iser_device {int dummy; } ;
struct ib_conn {struct iser_device* device; int /*<<< orphan*/ * qp; int /*<<< orphan*/  cma_id; TYPE_1__* comp; } ;
struct iser_conn {scalar_t__ rx_descs; struct ib_conn ib_conn; } ;
struct TYPE_4__ {int /*<<< orphan*/  connlist_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  active_qps; } ;

/* Variables and functions */
 TYPE_2__ ig ; 
 int /*<<< orphan*/  iser_device_try_release (struct iser_device*) ; 
 int /*<<< orphan*/  iser_free_rx_descriptors (struct iser_conn*) ; 
 int /*<<< orphan*/  iser_info (char*,struct iser_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_qp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iser_free_ib_conn_res(struct iser_conn *iser_conn,
				  bool destroy)
{
	struct ib_conn *ib_conn = &iser_conn->ib_conn;
	struct iser_device *device = ib_conn->device;

	iser_info("freeing conn %p cma_id %p qp %p\n",
		  iser_conn, ib_conn->cma_id, ib_conn->qp);

	if (ib_conn->qp != NULL) {
		mutex_lock(&ig.connlist_mutex);
		ib_conn->comp->active_qps--;
		mutex_unlock(&ig.connlist_mutex);
		rdma_destroy_qp(ib_conn->cma_id);
		ib_conn->qp = NULL;
	}

	if (destroy) {
		if (iser_conn->rx_descs)
			iser_free_rx_descriptors(iser_conn);

		if (device != NULL) {
			iser_device_try_release(device);
			ib_conn->device = NULL;
		}
	}
}
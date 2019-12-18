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
struct rdma_cm_id {struct nvmet_port* context; } ;
struct nvmet_rdma_queue {int dummy; } ;
struct nvmet_port {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 struct rdma_cm_id* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvmet_rdma_device_removal(struct rdma_cm_id *cm_id,
		struct nvmet_rdma_queue *queue)
{
	struct nvmet_port *port;

	if (queue) {
		/*
		 * This is a queue cm_id. we have registered
		 * an ib_client to handle queues removal
		 * so don't interfear and just return.
		 */
		return 0;
	}

	port = cm_id->context;

	/*
	 * This is a listener cm_id. Make sure that
	 * future remove_port won't invoke a double
	 * cm_id destroy. use atomic xchg to make sure
	 * we don't compete with remove_port.
	 */
	if (xchg(&port->priv, NULL) != cm_id)
		return 0;

	/*
	 * We need to return 1 so that the core will destroy
	 * it's own ID.  What a great API design..
	 */
	return 1;
}
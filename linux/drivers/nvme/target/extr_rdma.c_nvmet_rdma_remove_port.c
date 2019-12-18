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
struct rdma_cm_id {int dummy; } ;
struct nvmet_port {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 
 struct rdma_cm_id* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvmet_rdma_remove_port(struct nvmet_port *port)
{
	struct rdma_cm_id *cm_id = xchg(&port->priv, NULL);

	if (cm_id)
		rdma_destroy_id(cm_id);
}
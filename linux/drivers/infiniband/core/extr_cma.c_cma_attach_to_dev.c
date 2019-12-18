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
struct TYPE_2__ {size_t port_num; } ;
struct rdma_id_private {TYPE_1__ id; int /*<<< orphan*/  gid_type; } ;
struct cma_device {int /*<<< orphan*/  device; int /*<<< orphan*/ * default_gid_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cma_attach_to_dev (struct rdma_id_private*,struct cma_device*) ; 
 size_t rdma_start_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cma_attach_to_dev(struct rdma_id_private *id_priv,
			      struct cma_device *cma_dev)
{
	_cma_attach_to_dev(id_priv, cma_dev);
	id_priv->gid_type =
		cma_dev->default_gid_type[id_priv->id.port_num -
					  rdma_start_port(cma_dev->device)];
}
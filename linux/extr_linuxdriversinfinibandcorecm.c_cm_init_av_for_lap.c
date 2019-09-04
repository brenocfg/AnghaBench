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
struct rdma_ah_attr {int dummy; } ;
struct ib_wc {int /*<<< orphan*/  pkey_index; } ;
struct ib_grh {int dummy; } ;
struct cm_port {int /*<<< orphan*/  port_num; TYPE_1__* cm_dev; } ;
struct cm_av {int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  pkey_index; struct cm_port* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  ib_device; } ;

/* Variables and functions */
 int ib_init_ah_attr_from_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_wc*,struct ib_grh*,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_move_ah_attr (int /*<<< orphan*/ *,struct rdma_ah_attr*) ; 

__attribute__((used)) static int cm_init_av_for_lap(struct cm_port *port, struct ib_wc *wc,
			      struct ib_grh *grh, struct cm_av *av)
{
	struct rdma_ah_attr new_ah_attr;
	int ret;

	av->port = port;
	av->pkey_index = wc->pkey_index;

	/*
	 * av->ah_attr might be initialized based on past wc during incoming
	 * connect request or while sending out connect request. So initialize
	 * a new ah_attr on stack. If initialization fails, old ah_attr is
	 * used for sending any responses. If initialization is successful,
	 * than new ah_attr is used by overwriting old one.
	 */
	ret = ib_init_ah_attr_from_wc(port->cm_dev->ib_device,
				      port->port_num, wc,
				      grh, &new_ah_attr);
	if (ret)
		return ret;

	rdma_move_ah_attr(&av->ah_attr, &new_ah_attr);
	return 0;
}
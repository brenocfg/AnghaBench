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
struct mei_cl {scalar_t__ tx_flow_ctrl_creds; TYPE_1__* me_cl; } ;
struct TYPE_2__ {scalar_t__ tx_flow_ctrl_creds; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ mei_cl_is_fixed_address (struct mei_cl*) ; 
 scalar_t__ mei_cl_is_single_recv_buf (struct mei_cl*) ; 

__attribute__((used)) static int mei_cl_tx_flow_ctrl_creds_reduce(struct mei_cl *cl)
{
	if (WARN_ON(!cl || !cl->me_cl))
		return -EINVAL;

	if (mei_cl_is_fixed_address(cl))
		return 0;

	if (mei_cl_is_single_recv_buf(cl)) {
		if (WARN_ON(cl->me_cl->tx_flow_ctrl_creds <= 0))
			return -EINVAL;
		cl->me_cl->tx_flow_ctrl_creds--;
	} else {
		if (WARN_ON(cl->tx_flow_ctrl_creds <= 0))
			return -EINVAL;
		cl->tx_flow_ctrl_creds--;
	}
	return 0;
}
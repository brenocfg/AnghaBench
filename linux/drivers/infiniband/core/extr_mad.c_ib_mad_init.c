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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_MAD_QP_MAX_SIZE ; 
 int /*<<< orphan*/  IB_MAD_QP_MIN_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_mad_port_list ; 
 scalar_t__ ib_register_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mad_client ; 
 int /*<<< orphan*/  mad_recvq_size ; 
 int /*<<< orphan*/  mad_sendq_size ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int ib_mad_init(void)
{
	mad_recvq_size = min(mad_recvq_size, IB_MAD_QP_MAX_SIZE);
	mad_recvq_size = max(mad_recvq_size, IB_MAD_QP_MIN_SIZE);

	mad_sendq_size = min(mad_sendq_size, IB_MAD_QP_MAX_SIZE);
	mad_sendq_size = max(mad_sendq_size, IB_MAD_QP_MIN_SIZE);

	INIT_LIST_HEAD(&ib_mad_port_list);

	if (ib_register_client(&mad_client)) {
		pr_err("Couldn't register ib_mad client\n");
		return -EINVAL;
	}

	return 0;
}
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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ gid_tbl_len; } ;
struct rxe_port {TYPE_1__ attr; } ;
struct rxe_dev {struct rxe_port port; } ;
struct rdma_ah_attr {int dummy; } ;
struct TYPE_4__ {scalar_t__ sgid_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_AH_GRH ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 TYPE_2__* rdma_ah_read_grh (struct rdma_ah_attr*) ; 

int rxe_av_chk_attr(struct rxe_dev *rxe, struct rdma_ah_attr *attr)
{
	struct rxe_port *port;

	port = &rxe->port;

	if (rdma_ah_get_ah_flags(attr) & IB_AH_GRH) {
		u8 sgid_index = rdma_ah_read_grh(attr)->sgid_index;

		if (sgid_index > port->attr.gid_tbl_len) {
			pr_warn("invalid sgid index = %d\n", sgid_index);
			return -EINVAL;
		}
	}

	return 0;
}
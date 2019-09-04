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
struct rdma_ucm_create_id {int ps; int qp_type; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
 int EINVAL ; 
 int IB_QPT_RC ; 
 int IB_QPT_UD ; 
#define  RDMA_PS_IB 131 
#define  RDMA_PS_IPOIB 130 
#define  RDMA_PS_TCP 129 
#define  RDMA_PS_UDP 128 

__attribute__((used)) static int ucma_get_qp_type(struct rdma_ucm_create_id *cmd, enum ib_qp_type *qp_type)
{
	switch (cmd->ps) {
	case RDMA_PS_TCP:
		*qp_type = IB_QPT_RC;
		return 0;
	case RDMA_PS_UDP:
	case RDMA_PS_IPOIB:
		*qp_type = IB_QPT_UD;
		return 0;
	case RDMA_PS_IB:
		*qp_type = cmd->qp_type;
		return 0;
	default:
		return -EINVAL;
	}
}
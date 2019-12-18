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
struct TYPE_2__ {int ps; } ;
struct rdma_id_private {TYPE_1__ id; } ;
typedef  enum rdma_ucm_port_space { ____Placeholder_rdma_ucm_port_space } rdma_ucm_port_space ;

/* Variables and functions */
#define  RDMA_PS_IB 131 
#define  RDMA_PS_IPOIB 130 
#define  RDMA_PS_TCP 129 
#define  RDMA_PS_UDP 128 

__attribute__((used)) static enum rdma_ucm_port_space
cma_select_inet_ps(struct rdma_id_private *id_priv)
{
	switch (id_priv->id.ps) {
	case RDMA_PS_TCP:
	case RDMA_PS_UDP:
	case RDMA_PS_IPOIB:
	case RDMA_PS_IB:
		return id_priv->id.ps;
	default:

		return 0;
	}
}
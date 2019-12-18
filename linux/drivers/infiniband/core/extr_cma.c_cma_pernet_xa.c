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
struct xarray {int dummy; } ;
struct net {int dummy; } ;
struct cma_pernet {struct xarray ib_ps; struct xarray ipoib_ps; struct xarray udp_ps; struct xarray tcp_ps; } ;
typedef  enum rdma_ucm_port_space { ____Placeholder_rdma_ucm_port_space } rdma_ucm_port_space ;

/* Variables and functions */
#define  RDMA_PS_IB 131 
#define  RDMA_PS_IPOIB 130 
#define  RDMA_PS_TCP 129 
#define  RDMA_PS_UDP 128 
 struct cma_pernet* cma_pernet (struct net*) ; 

__attribute__((used)) static
struct xarray *cma_pernet_xa(struct net *net, enum rdma_ucm_port_space ps)
{
	struct cma_pernet *pernet = cma_pernet(net);

	switch (ps) {
	case RDMA_PS_TCP:
		return &pernet->tcp_ps;
	case RDMA_PS_UDP:
		return &pernet->udp_ps;
	case RDMA_PS_IPOIB:
		return &pernet->ipoib_ps;
	case RDMA_PS_IB:
		return &pernet->ib_ps;
	default:
		return NULL;
	}
}
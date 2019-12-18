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
typedef  enum rdma_ucm_port_space { ____Placeholder_rdma_ucm_port_space } rdma_ucm_port_space ;

/* Variables and functions */
 struct xarray* cma_pernet_xa (struct net*,int) ; 
 int /*<<< orphan*/  xa_erase (struct xarray*,int) ; 

__attribute__((used)) static void cma_ps_remove(struct net *net, enum rdma_ucm_port_space ps,
			  int snum)
{
	struct xarray *xa = cma_pernet_xa(net, ps);

	xa_erase(xa, snum);
}
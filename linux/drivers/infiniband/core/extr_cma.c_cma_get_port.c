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
struct rdma_id_private {int dummy; } ;
typedef  enum rdma_ucm_port_space { ____Placeholder_rdma_ucm_port_space } rdma_ucm_port_space ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 int EPROTONOSUPPORT ; 
 int cma_alloc_any_port (int,struct rdma_id_private*) ; 
 scalar_t__ cma_any_port (int /*<<< orphan*/ ) ; 
 scalar_t__ cma_family (struct rdma_id_private*) ; 
 int cma_select_ib_ps (struct rdma_id_private*) ; 
 int cma_select_inet_ps (struct rdma_id_private*) ; 
 int /*<<< orphan*/  cma_src_addr (struct rdma_id_private*) ; 
 int cma_use_port (int,struct rdma_id_private*) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_get_port(struct rdma_id_private *id_priv)
{
	enum rdma_ucm_port_space ps;
	int ret;

	if (cma_family(id_priv) != AF_IB)
		ps = cma_select_inet_ps(id_priv);
	else
		ps = cma_select_ib_ps(id_priv);
	if (!ps)
		return -EPROTONOSUPPORT;

	mutex_lock(&lock);
	if (cma_any_port(cma_src_addr(id_priv)))
		ret = cma_alloc_any_port(ps, id_priv);
	else
		ret = cma_use_port(ps, id_priv);
	mutex_unlock(&lock);

	return ret;
}
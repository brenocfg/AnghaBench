#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  net; } ;
struct TYPE_6__ {TYPE_1__ dev_addr; } ;
struct TYPE_7__ {TYPE_2__ addr; } ;
struct TYPE_8__ {TYPE_3__ route; } ;
struct rdma_id_private {int /*<<< orphan*/  reuseaddr; TYPE_4__ id; } ;
struct rdma_bind_list {int dummy; } ;
typedef  enum rdma_ucm_port_space { ____Placeholder_rdma_ucm_port_space } rdma_ucm_port_space ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_BIND_SERVICE ; 
 int EACCES ; 
 unsigned short PROT_SOCK ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int cma_alloc_port (int,struct rdma_id_private*,unsigned short) ; 
 int /*<<< orphan*/  cma_bind_port (struct rdma_bind_list*,struct rdma_id_private*) ; 
 int cma_check_port (struct rdma_bind_list*,struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cma_port (int /*<<< orphan*/ ) ; 
 struct rdma_bind_list* cma_ps_find (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  cma_src_addr (struct rdma_id_private*) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cma_use_port(enum rdma_ucm_port_space ps,
			struct rdma_id_private *id_priv)
{
	struct rdma_bind_list *bind_list;
	unsigned short snum;
	int ret;

	snum = ntohs(cma_port(cma_src_addr(id_priv)));
	if (snum < PROT_SOCK && !capable(CAP_NET_BIND_SERVICE))
		return -EACCES;

	bind_list = cma_ps_find(id_priv->id.route.addr.dev_addr.net, ps, snum);
	if (!bind_list) {
		ret = cma_alloc_port(ps, id_priv, snum);
	} else {
		ret = cma_check_port(bind_list, id_priv, id_priv->reuseaddr);
		if (!ret)
			cma_bind_port(bind_list, id_priv);
	}
	return ret;
}
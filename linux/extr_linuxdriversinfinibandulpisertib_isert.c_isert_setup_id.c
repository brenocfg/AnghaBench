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
struct sockaddr {int dummy; } ;
struct rdma_cm_id {struct sockaddr* context; } ;
struct isert_np {struct iscsi_np* np; } ;
struct iscsi_np {struct rdma_cm_id np_sockaddr; } ;

/* Variables and functions */
 struct rdma_cm_id* ERR_PTR (int) ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 scalar_t__ IS_ERR (struct rdma_cm_id*) ; 
 int PTR_ERR (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  isert_cma_handler ; 
 int /*<<< orphan*/  isert_dbg (char*,struct rdma_cm_id*,struct sockaddr*) ; 
 int /*<<< orphan*/  isert_err (char*,int) ; 
 int rdma_bind_addr (struct rdma_cm_id*,struct sockaddr*) ; 
 struct rdma_cm_id* rdma_create_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct isert_np*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 
 int rdma_listen (struct rdma_cm_id*,int /*<<< orphan*/ ) ; 

struct rdma_cm_id *
isert_setup_id(struct isert_np *isert_np)
{
	struct iscsi_np *np = isert_np->np;
	struct rdma_cm_id *id;
	struct sockaddr *sa;
	int ret;

	sa = (struct sockaddr *)&np->np_sockaddr;
	isert_dbg("ksockaddr: %p, sa: %p\n", &np->np_sockaddr, sa);

	id = rdma_create_id(&init_net, isert_cma_handler, isert_np,
			    RDMA_PS_TCP, IB_QPT_RC);
	if (IS_ERR(id)) {
		isert_err("rdma_create_id() failed: %ld\n", PTR_ERR(id));
		ret = PTR_ERR(id);
		goto out;
	}
	isert_dbg("id %p context %p\n", id, id->context);

	ret = rdma_bind_addr(id, sa);
	if (ret) {
		isert_err("rdma_bind_addr() failed: %d\n", ret);
		goto out_id;
	}

	ret = rdma_listen(id, 0);
	if (ret) {
		isert_err("rdma_listen() failed: %d\n", ret);
		goto out_id;
	}

	return id;
out_id:
	rdma_destroy_id(id);
out:
	return ERR_PTR(ret);
}
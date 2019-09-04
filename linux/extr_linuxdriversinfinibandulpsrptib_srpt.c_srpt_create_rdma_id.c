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
struct rdma_cm_id {int dummy; } ;
typedef  int /*<<< orphan*/  addr_str ;

/* Variables and functions */
 struct rdma_cm_id* ERR_PTR (int) ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 scalar_t__ IS_ERR (struct rdma_cm_id*) ; 
 int PTR_ERR (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int rdma_bind_addr (struct rdma_cm_id*,struct sockaddr*) ; 
 struct rdma_cm_id* rdma_create_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 
 int rdma_listen (struct rdma_cm_id*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,struct sockaddr*) ; 
 int /*<<< orphan*/  srpt_rdma_cm_handler ; 

__attribute__((used)) static struct rdma_cm_id *srpt_create_rdma_id(struct sockaddr *listen_addr)
{
	struct rdma_cm_id *rdma_cm_id;
	int ret;

	rdma_cm_id = rdma_create_id(&init_net, srpt_rdma_cm_handler,
				    NULL, RDMA_PS_TCP, IB_QPT_RC);
	if (IS_ERR(rdma_cm_id)) {
		pr_err("RDMA/CM ID creation failed: %ld\n",
		       PTR_ERR(rdma_cm_id));
		goto out;
	}

	ret = rdma_bind_addr(rdma_cm_id, listen_addr);
	if (ret) {
		char addr_str[64];

		snprintf(addr_str, sizeof(addr_str), "%pISp", listen_addr);
		pr_err("Binding RDMA/CM ID to address %s failed: %d\n",
		       addr_str, ret);
		rdma_destroy_id(rdma_cm_id);
		rdma_cm_id = ERR_PTR(ret);
		goto out;
	}

	ret = rdma_listen(rdma_cm_id, 128);
	if (ret) {
		pr_err("rdma_listen() failed: %d\n", ret);
		rdma_destroy_id(rdma_cm_id);
		rdma_cm_id = ERR_PTR(ret);
	}

out:
	return rdma_cm_id;
}
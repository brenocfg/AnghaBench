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
struct rdma_cm_id {int dummy; } ;
struct isert_conn {int /*<<< orphan*/  qp; } ;
struct isert_comp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct isert_comp* isert_comp_get (struct isert_conn*) ; 
 int /*<<< orphan*/  isert_comp_put (struct isert_comp*) ; 
 int /*<<< orphan*/  isert_create_qp (struct isert_conn*,struct isert_comp*,struct rdma_cm_id*) ; 

__attribute__((used)) static int
isert_conn_setup_qp(struct isert_conn *isert_conn, struct rdma_cm_id *cma_id)
{
	struct isert_comp *comp;
	int ret;

	comp = isert_comp_get(isert_conn);
	isert_conn->qp = isert_create_qp(isert_conn, comp, cma_id);
	if (IS_ERR(isert_conn->qp)) {
		ret = PTR_ERR(isert_conn->qp);
		goto err;
	}

	return 0;
err:
	isert_comp_put(comp);
	return ret;
}
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
struct TYPE_4__ {struct resp_res* resources; } ;
struct TYPE_3__ {int max_dest_rd_atomic; } ;
struct rxe_qp {TYPE_2__ resp; TYPE_1__ attr; } ;
struct resp_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_rd_atomic_resource (struct rxe_qp*,struct resp_res*) ; 
 int /*<<< orphan*/  kfree (struct resp_res*) ; 

__attribute__((used)) static void free_rd_atomic_resources(struct rxe_qp *qp)
{
	if (qp->resp.resources) {
		int i;

		for (i = 0; i < qp->attr.max_dest_rd_atomic; i++) {
			struct resp_res *res = &qp->resp.resources[i];

			free_rd_atomic_resource(qp, res);
		}
		kfree(qp->resp.resources);
		qp->resp.resources = NULL;
	}
}
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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {struct resp_res* resources; } ;
struct TYPE_3__ {int max_dest_rd_atomic; } ;
struct rxe_qp {TYPE_2__ resp; TYPE_1__ attr; } ;
struct resp_res {scalar_t__ type; int /*<<< orphan*/  last_psn; int /*<<< orphan*/  first_psn; } ;

/* Variables and functions */
 scalar_t__ psn_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resp_res *find_resource(struct rxe_qp *qp, u32 psn)
{
	int i;

	for (i = 0; i < qp->attr.max_dest_rd_atomic; i++) {
		struct resp_res *res = &qp->resp.resources[i];

		if (res->type == 0)
			continue;

		if (psn_compare(psn, res->first_psn) >= 0 &&
		    psn_compare(psn, res->last_psn) <= 0) {
			return res;
		}
	}

	return NULL;
}
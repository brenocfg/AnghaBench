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
struct rdma_ah_attr {int dummy; } ;
struct ib_ah {int dummy; } ;
struct qedr_ah {struct ib_ah ibah; int /*<<< orphan*/  attr; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct qedr_ah* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_copy_ah_attr (int /*<<< orphan*/ *,struct rdma_ah_attr*) ; 

struct ib_ah *qedr_create_ah(struct ib_pd *ibpd, struct rdma_ah_attr *attr,
			     struct ib_udata *udata)
{
	struct qedr_ah *ah;

	ah = kzalloc(sizeof(*ah), GFP_ATOMIC);
	if (!ah)
		return ERR_PTR(-ENOMEM);

	rdma_copy_ah_attr(&ah->attr, attr);

	return &ah->ibah;
}